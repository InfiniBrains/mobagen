#include "CrystalPicker.h"
#include "Logger.h"
#include "Crystal.h"
#include "Matrix.h"
#include "Menu.h"

CrystalPicker::CrystalPicker(std::map<Crystal::CrystalType, std::shared_ptr<Texture>> textures, std::map<Crystal::CrystalType, std::shared_ptr<Material>> materials)
{
	m_materials = materials;
	m_textures = textures;
	firstSelection = nullptr;
	secondSelection = nullptr;
}

void CrystalPicker::updateInput(Input *input, double delta) {
  if (getParent()->getComponent<Menu>()->getTime() < 0)
		return;
  auto engine = getEngine();
  if (input->mousePressedState(SDL_BUTTON_LEFT)==Input::InputState::JUSTPRESSED) {
    Ray ray = Ray::getPickRay(input->getMousePosition(),
                              engine->getWindow()->getViewport(),
                              engine->getGLManager()->getViewMatrix(),
                              engine->getGLManager()->getProjectionMatrix());

    Entity *pickedEntity = getEngine()->getPhysicsManager()->pick(&ray);
	
	// check if picked some entity
	if (pickedEntity == nullptr)
	  return;
	else
	  log_info("found entity at: (%f,%f,%f)", pickedEntity->getPosition().x, pickedEntity->getPosition().y, pickedEntity->getPosition().z);

	auto matrixpos = Vec3ToMatrixPosition(pickedEntity->getPosition().xyz());
	log_info("x,y = %d,%d",matrixpos.x,matrixpos.y);

	if (firstSelection != nullptr && secondSelection != nullptr)
	  return;
	else if (firstSelection != nullptr && pickedEntity == firstSelection){
		pickedEntity->getComponent<Crystal>()->decreaseSize();
		firstSelection = nullptr;
	}
	else if (firstSelection != nullptr && secondSelection == nullptr) {
	  secondSelection = pickedEntity;
	  pickedEntity->getComponent<Crystal>()->increaseSize();
	  auto firstPosition = Vec3ToMatrixPosition(firstSelection->getPosition().xyz());
	  auto secondPosition = Vec3ToMatrixPosition(secondSelection->getPosition().xyz());
	  // check if positions are near
	  auto deltaX = firstPosition.x - secondPosition.x;
	  auto deltaY = firstPosition.y - secondPosition.y;
	  if (deltaX*deltaX + deltaY * deltaY >1 )
	  {
		  firstSelection->getComponent<Crystal>()->decreaseSize();
		  secondSelection->getComponent<Crystal>()->decreaseSize();

		  firstSelection = nullptr;
		  secondSelection = nullptr;
		  return;
	  }

	  // check if matrix allow swap
	  if (getParent()->getComponent<Matrix>()->canSwap(firstPosition.x, firstPosition.y, secondPosition.x, secondPosition.y)) 
	  {
		  // tel crystal to move
		  firstSelection->getComponent<Crystal>()->swapPositions(secondSelection->getComponent<Crystal>(),false);
		  secondSelection->getComponent<Crystal>()->swapPositions(firstSelection->getComponent<Crystal>(),false);
		  // update matrix
		  getParent()->getComponent<Matrix>()->setElement(firstPosition.x, firstPosition.y, secondSelection->getComponent<Crystal>());
		  getParent()->getComponent<Matrix>()->setElement(secondPosition.x, secondPosition.y, firstSelection->getComponent<Crystal>());
	  }
	  else
	  {
		  firstSelection->getComponent<Crystal>()->swapPositions(secondSelection->getComponent<Crystal>(), true);
		  secondSelection->getComponent<Crystal>()->swapPositions(firstSelection->getComponent<Crystal>(), true);
	  }
	}
	else if (firstSelection == nullptr){
	  firstSelection = pickedEntity;
	  pickedEntity->getComponent<Crystal>()->increaseSize();
	}
  }
}

glm::vec3 CrystalPicker::MatrixPositionToVec3(int x, int y)
{
  return glm::vec3(30 - x * 43, -1, 180 - y * 43);
}

glm::i32vec2 CrystalPicker::Vec3ToMatrixPosition(glm::vec3 pos)
{
  return glm::i32vec2(nearbyintf((30 - pos.x) / 43), nearbyint((180 - pos.z) / 43));
}

const char* CrystalPicker::getType()
{
  return "CRYSTALPICKER";
}

void CrystalPicker::deselect()
{
  if (firstSelection != nullptr) {
	firstSelection->getComponent<Crystal>()->decreaseSize();
	firstSelection = nullptr;
  }

  if (secondSelection != nullptr) {
	secondSelection->getComponent<Crystal>()->decreaseSize();
	secondSelection = nullptr;
  }
}

std::shared_ptr<Texture> CrystalPicker::getTexture(Crystal::CrystalType color)
{
	return m_textures[color];
}

std::shared_ptr<Material> CrystalPicker::getMaterial(Crystal::CrystalType color)
{
	return m_materials[color];
}

