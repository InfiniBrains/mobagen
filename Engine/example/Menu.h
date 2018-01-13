#pragma once

#include "Engine.h"

class Menu : public Component
{
public:
	~Menu() override{};
	const char* getType() override;
	void updateInput(Input* input, int delta) override {};
	void update(int delta) override {};
	void render(Shader* shader) override {};
	void registerWithEngine(Engine* engine) override {};
	void deregisterFromEngine(Engine* engine) override {};
	void onGUI(ImGuiContext* context) override;
};
