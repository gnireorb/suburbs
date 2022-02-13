#include "common.hpp"

namespace youtube_dlp
{
	static void render()
	{
		if (ImGui::CollapsingHeader("youtube-dlp") && std::filesystem::exists("yt-dlp.exe"))
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
	}
}