#include "common.hpp"

#include "helpers/ngrok.hpp"

namespace ngrok_helper
{
	static void render()
	{
		if (ImGui::CollapsingHeader("ngrok-helper"))
		{
			static int port{};
			ImGui::InputInt("Port", &port);

			ImGui::Separator();

			static int region{};
			ImGui::PushItemWidth(-1);
			ImGui::Combo("Region", &region, ngrok::regions, IM_ARRAYSIZE(ngrok::regions));
			ImGui::PopItemWidth();

			ImGui::Separator();

			static int protocol_type{};
			ImGui::PushItemWidth(-1);
			ImGui::Combo("Protocol Type", &protocol_type, ngrok::protocol_type, IM_ARRAYSIZE(ngrok::protocol_type));
			ImGui::PopItemWidth();

			ImGui::Separator();

			static std::string public_url{};
			ImGui::InputText("Public Url", &public_url);
			if (ImGui::Button("Get Public Url"))
			{
				auto t = []()
				{
					public_url = ngrok::get_public_url();
				};
				std::thread(t).detach();
			}

			ImGui::Separator();

			static std::string authtoken{};
			ImGui::InputText("Authtoken", &authtoken);
			if (ImGui::Button("Set Authtoken"))
			{
				auto t = []()
				{
					system(fmt::format("ngrok authtoken {}", authtoken).c_str());
				};
				std::thread(t).detach();
			}

			ImGui::Separator();

			if (ImGui::Button("Create Tunnel"))
			{
				auto t = []()
				{
					ngrok::create_tunnel(protocol_type == 0 ? true : false, port, region);
				};
				std::thread(t).detach();
			}
			ImGui::Separator();
			if (ImGui::Button("Download Ngrok"))
			{
				auto t = []()
				{
					ngrok::download(fmt::format("https://github.com/gnireorb/ngrok-helper/releases/download/{}/ngrok.exe", ngrok::version).c_str());
				};
				std::thread(t).detach();
			}
		}
	}
}