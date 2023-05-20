#pragma once

namespace control {
	static class rspControll
	{
	public:
		static inline void sendToSorter() {
			secondBeltEngieneStart();
			while (!isAllInsideSorter)
			{
				//wait
			}
			secondBeltEngieneStop();
		}
		static inline void sendToPress() {
			firstBeltEngieneStart();
			while (!isUnderPress())
			{
				//wait
			}
			firstBeltEngieneStop();

		}
		static inline void SendFromWerhouse() {
			firstBeltEngieneStart();
			while (!isAllInsideFurnace)
			{
				//wait
			}
			firstBeltEngieneStop();
		}
		static inline void setFurnacePower(int power) {
			//set power at power%
			return;
		}

	private:
		static void firstBeltEngieneStart() {
			return;
		}
		static void firstBeltEngieneStop() {
			return;
		}
		static void secondBeltEngieneStart() {
			return;
		}
		static void secondBeltEngieneStop() {
			return;
		}
		static bool isAllInsideFurnace() {
			return true;
		}
		static bool isAllInsideSorter() {
			return true;
		}
		static bool isUnderPress() {
			return true;
		}
	};

	
	

}