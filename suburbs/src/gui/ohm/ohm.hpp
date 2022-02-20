#include "common.hpp"

namespace ohm
{
	static void render()
	{
		if (ImGui::CollapsingHeader("ohm"))
		{
			static int voltage{};
			static float cost_per_hour, cost_per_day, cost_per_month, cost_per_year, current, wattage, kilowatt_hour{};
			static float kilowatt_value{ 0.75f };
			
			ImGui::PushItemWidth(150.f);
			ImGui::InputFloat("Kilowatt Value (R$)", &kilowatt_value);
			ImGui::InputFloat("Current (A)", &current);
			ImGui::InputInt("Voltage (V)", &voltage);
			ImGui::PopItemWidth();
			if (ImGui::Button("Calculate"))
			{
				wattage = current * voltage;
				kilowatt_hour = wattage / 1000;
				cost_per_hour = kilowatt_hour * kilowatt_value;
				cost_per_day = cost_per_hour * 24;
				cost_per_month = cost_per_hour * 24 * 30;
				cost_per_year = cost_per_hour * 24 * 365;
			}
			ImGui::PushItemWidth(150.f);
			ImGui::InputFloat("Wattage (W)", &wattage);
			ImGui::InputFloat("Kilowatt-hour (KWH)", &kilowatt_hour);
			ImGui::InputFloat("Cost per hour (R$)", &cost_per_hour);
			ImGui::InputFloat("Cost per day (R$)", &cost_per_day);
			ImGui::InputFloat("Cost per month (R$)", &cost_per_month);
			ImGui::InputFloat("Cost per year (R$)", &cost_per_year);
			ImGui::PopItemWidth();
		}
	}
}