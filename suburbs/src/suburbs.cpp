#include "common.hpp"

#include "backend/imgui_implementation.hpp"
#include "backend/fonts.hpp"

#include "util/util.hpp"

int main()
{
	spdlog::set_pattern("[%H:%M:%S] [%t] [%^%l%$] %v");

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, backend::imgui_implementation::wndproc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("suburbs"), NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("suburbs"), WS_OVERLAPPEDWINDOW, 100, 100, 405, 720, NULL, NULL, wc.hInstance, NULL);

	if (!backend::imgui_implementation::create_device_d3d(hwnd))
	{
		backend::imgui_implementation::cleanup_device_d3d();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	::ShowWindow(hwnd, SW_SHOWDEFAULT); ::UpdateWindow(hwnd);

	ImGui::CreateContext();

	backend::imgui_implementation::apply_style();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(backend::imgui_implementation::g_pd3ddevice);

	ImFontConfig ruda_regular_config, ruda_bold_config{};
	std::strcpy(ruda_regular_config.Name, "Ruda-Regular"); std::strcpy(ruda_bold_config.Name, "Ruda-Bold");

	ImFont* ruda_regular = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(backend::fonts::ruda_regular), sizeof(backend::fonts::ruda_regular), 20.f, &ruda_regular_config); ImFont* ruda_bold = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(backend::fonts::ruda_bold), sizeof(backend::fonts::ruda_bold), 20.f, &ruda_bold_config);
	IM_ASSERT(ruda_regular != NULL); IM_ASSERT(ruda_bold != NULL);

	bool done = { false };
	while (!done)
	{
		MSG msg{};
		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}
		if (done)
			break;

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		{
			ImGui::SetNextWindowSize(ImVec2(360, 656), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(15, 12), ImGuiCond_FirstUseEver);
			if (ImGui::Begin("suburbs", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
			{
				if (ImGui::CollapsingHeader("youtube-dlp"))
				{
					if (util::file_exists("yt-dlp.exe"))
					{
						static std::string url{};
						ImGui::InputText("URL##url", &url);
						const char* const _type[]{ "audio", "video" };
						static int type{};
						ImGui::Combo("Type##type", &type, _type, IM_ARRAYSIZE(_type));
						const char* const _audio_quality[]{ "best (0)", "half (5)", "worst (10)" };
						static int audio_quality{};
						const char* const _video_format[]{ "mp4", "mkv", "webm" };
						static int video_format{};
						switch (type)
						{
						case 0:
						{
							ImGui::Combo("Audio Quality##audio_quality", &audio_quality, _audio_quality, IM_ARRAYSIZE(_audio_quality));
							break;
						}
						case 1:
						{
							ImGui::Combo("Video Format##video_format", &video_format, _video_format, IM_ARRAYSIZE(_video_format));
							break;
						}
						}
						if (ImGui::Button("Download"))
						{
							auto download = []()
							{
								if (type == 0)
									switch (audio_quality)
									{
									case 0:
									{
										std::system(fmt::format("yt-dlp -x --audio-quality {} --audio-format mp3 {}", 0, url).c_str());
										break;
									}
									case 1:
									{
										std::system(fmt::format("yt-dlp -x --audio-quality {} --audio-format mp3 {}", 5, url).c_str());
										break;
									}
									case 2:
									{
										std::system(fmt::format("yt-dlp -x --audio-quality {} --audio-format mp3 {}", 10, url).c_str());
										break;
									}
									}
								else
									switch (video_format)
									{
									case 0:
									{
										std::system(fmt::format("yt-dlp --format mp4 {}", url).c_str());
										break;
									}
									case 1:
									{
										std::system(fmt::format("yt-dlp --format mkv {}", url).c_str());
										break;
									}
									case 2:
									{
										std::system(fmt::format("yt-dlp --format webm {}", url).c_str());
										break;
									}
									}
							};
							std::thread(download).detach();
						}
					}
					ImGui::Separator();
				}
				ImGui::Text("github.com/gnireorb/suburbs");
				ImGui::End();
			}
		}

		ImGui::EndFrame();

		backend::imgui_implementation::g_pd3ddevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		backend::imgui_implementation::g_pd3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		backend::imgui_implementation::g_pd3ddevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		backend::imgui_implementation::g_pd3ddevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(31, 46, 74, 255), 1.0f, 0);

		if (backend::imgui_implementation::g_pd3ddevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			backend::imgui_implementation::g_pd3ddevice->EndScene();
		}

		if (backend::imgui_implementation::g_pd3ddevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST && backend::imgui_implementation::g_pd3ddevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			backend::imgui_implementation::reset_device();
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	backend::imgui_implementation::cleanup_device_d3d();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	return TRUE;
}