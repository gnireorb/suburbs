#include "HTTPRequest.hpp"

#include "common.hpp"

namespace ngrok
{
	static const char* const version{ "v1.6" };
	static const char* const regions[]{ "south america (sa)", "north america (us)", "europe (eu)", "asia (ap)", "australia (au)" };
	static const char* const protocol_type[]{ "tcp", "http" };

	static bool create_tunnel(bool tcp, int port, int region)
	{
		auto ngrok_tcp = [](bool is_tcp, int port, const char* region)
		{
			auto _system = [](bool is_tcp, int port, const char* region)
			{
				system(fmt::format("ngrok {} {} --region {}", is_tcp ? "tcp" : "http", port, region).c_str());
			};
			std::thread(_system, is_tcp, port, region).detach();
		};

		if (region >= 4 || region < 0)
			return false;

		switch (region)
		{
		case 0:
			ngrok_tcp(tcp, port, "sa");
			break;
		case 1:
			ngrok_tcp(tcp, port, "us");
			break;
		case 2:
			ngrok_tcp(tcp, port, "eu");
			break;
		case 3:
			ngrok_tcp(tcp, port, "ap");
			break;
		case 4:
			ngrok_tcp(tcp, port, "au");
			break;
		}

		return true;
	}

	static const char* get_public_url()
	{
		http::Request request("http://127.0.0.1:4040/api/tunnels");
		const auto response = request.send("GET");
		const auto json = nlohmann::json::parse(std::string{ response.body.begin(), response.body.end() });
		for (auto& tunnels : json["tunnels"])
		{
			return tunnels["public_url"].get<std::string>().erase(0, 6).c_str();
		}
		return ("undefined");
	}

	static bool download(const char* url)
	{
		if (!std::filesystem::exists("ngrok.exe"))
		{
			auto result = URLDownloadToFile(nullptr, url, "ngrok.exe", 0, nullptr);
			switch (result)
			{
			case E_OUTOFMEMORY:
			{
				spdlog::error("There is insufficient memory to complete the operation. E_OUTOFMEMORY");
				break;
			}
			case INET_E_DOWNLOAD_FAILURE:
			{
				spdlog::error("The specified resource or callback interface was invalid. INET_E_DOWNLOAD_FAILURE");
				break;
			}
			case S_OK:
			{
				spdlog::info("O executavel do ngrok foi baixado com sucesso. S_OK");
				return true;
			}
			}

			return false;
		}

		return false;
	}
}