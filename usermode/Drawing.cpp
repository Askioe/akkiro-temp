#include "Drawing.h"
LPCSTR Drawing::lpWindowName = " akkiro.zzz ";
ImVec2 Drawing::vWindowSize = { 750, 450 };
ImGuiWindowFlags Drawing::WindowFlags = { ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse };
bool Drawing::bDraw = true;


void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}



void ImGui_SetStyle() {
	auto& style = ImGui::GetStyle();
	//style.Alpha = 1.0f;
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.29f, 0.29f, 0.29f, 0.70f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.WindowRounding = { 0 };
	style.TabRounding = { 0 };
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.ScrollbarRounding = { 9.0f };
	style.ScrollbarSize = { 8.0f };
	style.WindowMenuButtonPosition = { 0 };
}

void Drawing::Draw()
{

	if (isActive())
	{
		ImGui_SetStyle();
		ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
		ImGui::SetNextWindowBgAlpha(2.0);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
			//ImGui::ShowStyleEditor();
			static const char* items[]
			{
				"Head",
				"Neck",
				"Chest",
			};

			static int selected = 0;
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("#", tab_bar_flags)) {
				if (ImGui::BeginTabItem("Aimbot"))
				{
					if (ImGui::BeginTable("table2", 2))
					{
						for (int row = 0; row < 1; row++)
						{
							ImGui::TableNextRow();
							ImGui::TableNextColumn();
							ImGui::Text("Aimbot:");
							ImGui::Checkbox("##Aimbot", &CGlobals::Aimbot);
							ImGui::SameLine();
							ImGui::Text("Enabled");
							ImGui::Spacing();
							ImGui::Checkbox("##AutoAim", &CGlobals::AutoAim);
							ImGui::SameLine();
							ImGui::Text("Auto Aim");
							ImGui::Spacing();
							ImGui::Text("Smoothing:");
							ImGui::SameLine();
							ImGui::SliderFloat(" ", &CGlobals::Smoothing, 0.0f, 1.0f);
							ImGui::Spacing();
							ImGui::Text("Hitboxes: ");
							ImGui::SameLine();
							ImGui::ListBox(" ", &selected, items, 3);
							ImGui::TableNextColumn();
							ImGui::Text("RCS:");
							ImGui::Checkbox("##RCS", &CGlobals::RCS);
							ImGui::SameLine();
							ImGui::Text("Enabled");
							ImGui::TableNextRow();
							ImGui::TableNextColumn();
						}
						ImGui::EndTable();
					}
					ImGui::EndTabItem();

				}
				if (ImGui::BeginTabItem("Triggerbot"))
				{
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Visuals"))
				{
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc"))
				{
					ImGui::Checkbox("Bhop", &CGlobals::Bhop);
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}


		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
