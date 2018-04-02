#pragma once

#include "Engine.h"

class Menu : public Component
{
public:
	const char* getType() override;
	void updateInput(Input* input, double delta) override {};
	void update(double delta) override;
	void render(Shader* shader) override {};
	void registerWithEngine(Engine* engine) override {};
	void deregisterFromEngine(Engine* engine) override {};
	void onGUI(ImGuiContext* context) override;
	void addScore(int value);
	double getTime();
private:
	double m_remainingTime = 60;
	int m_score = 0;
};
