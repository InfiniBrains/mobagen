#include "Menu.h"
#include <imgui.h>

const char* Menu::getType()
{
	return "MENU";
}

void Menu::onGUI(ImGuiContext* context)
{
	ImGui::SetCurrentContext(context);
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Assets"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("GameObject"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Component"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Window"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}
