#pragma once
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <map>
#include <string>
#include "../MeshObj/cMeshObj.h"
#include "../Light/cLightManager.h"
#include <vector>
#include "../Game/cRobot.h"

class cGUI
{
public:
	cGUI();
	~cGUI();

	bool ImGUI_init(GLFWwindow* window);
	void ImGUI_shutdown();
	bool ImGUICreateFrame();
	bool ImGUI_render();
	bool ImGUI_update();

	std::vector<cRobot*>* vRobot_;
	std::vector<cMeshObj*>* pVecInstanceMeshObj;
	cLight* pLight[MAX_LIGHT_SOURCE];
};

