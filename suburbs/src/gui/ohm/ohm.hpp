#include "common.hpp"

namespace ohm
{
	static void render()
	{
		if (ImGui::CollapsingHeader("ohm"))
		{
			static int voltage{};
			static float cost, month_cost, current, wattage, kilowatt_hour{};
			static float kilowatt_value{ 0.75f };
			
			ImGui::InputFloat("Kilowatt Value (R$)", &kilowatt_value);
			ImGui::InputFloat("Current (A)", &current);
			ImGui::InputInt("Voltage (V)", &voltage);
			if (ImGui::Button("Calculate"))
			{
				wattage = current * voltage;
				kilowatt_hour = wattage / 1000;
				cost = kilowatt_hour * kilowatt_value;
				month_cost = cost * 30;
			}
			ImGui::InputFloat("Wattage (W)", &wattage);
			ImGui::InputFloat("Kilowatt-hour (KWH)", &kilowatt_hour);
			ImGui::InputFloat("Cost (R$)", &cost);
			ImGui::InputFloat("Month Cost (R$)", &month_cost);
		}
	}
}