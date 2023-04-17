#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<time.h>
#include<bits/stdc++.h>

using namespace std;

class Flight
{
public:

	Flight()
	{
		flightNumber = "---";
		oCity = "Banglore";
		dCity = "Pune";
		airFare = 3500.00;	
		airOp = "Indigo";

	}

	Flight(string fNumber, string sCity, string destCity, float aFare, string airOperator): flightNumber(fNumber)
	, oCity(sCity),dCity(destCity),airFare(aFare), airOp(airOperator)
	{
		
	}

	~Flight()
	{

	}

	void printFlightDetails(const Flight & fdetails)
	{	
		cout << "Origin City" << " <====> " << "Destination City" << endl;
		cout << fdetails.oCity << "                     " << fdetails.dCity << endl;
		cout << "Flight Number              " << fdetails.flightNumber << endl;
		cout << "Fare                       " << fdetails.airFare << endl;
		cout << "Operator                   " << fdetails.airOp << endl;
	}

public:
	string flightNumber, oCity, dCity;
	float airFare;
	string airOp;

};


class FlightDataBase:public Flight
{

public:
	FlightDataBase(){}
	
	~FlightDataBase(){}

	void AddTrip(string flightNum, string originCity, string destCity, float fare, string airOp)
	{
		Flight tempFlight(flightNum, originCity, destCity, fare, airOp);
		printFlightDetails(tempFlight);
		FlightDb.insert(pair<string, Flight>(flightNum, tempFlight));
	}

	void removeTrip(string flightNum)
	{
		if(FlightDb.size()>0)
		{
			if(FlightDb.find(flightNum) != FlightDb.end())
			{
				FlightDb.erase(flightNum);
			}
		}
	}

	void UpdateFareByTrip(string flightNum, float airFare)
	{
		if(FlightDb.size()>0)
		{
			if(FlightDb.find(flightNum) != FlightDb.end())
			{
				Flight updateFlightFare = FlightDb.at(flightNum);
				updateFlightFare.airFare = airFare;
				FlightDb.at(flightNum)=updateFlightFare;
				printFlightDetails(FlightDb.at(flightNum));
			}
		}
	}

	void DisplayAllTrips()
	{
		map<string, Flight>::iterator it = FlightDb.begin();

		cout << "=========================================================" << endl;
		while(it != FlightDb.end())
		{
			printFlightDetails(it->second);
			it++;
		}
		cout << "=========================================================" << endl;
	}

	Flight& FindFlightByNumber(string flightNum)
	{
		bool found = false;
		if(FlightDb.size()>0)
		{
			if(FlightDb.find(flightNum) != FlightDb.end())
			{
				found = true;
			}
		}

		return FlightDb.at(flightNum);	
	}
	
	vector<Flight> FindFlightsByOriginCity(string oCity)
	{
		vector<Flight> storeFlightData;

		map<string, Flight>::iterator it = FlightDb.begin();

		while(it != FlightDb.end())
		{
			Flight tempFDetails = it->second;
			if(it->second.oCity.compare(oCity) == 0)
				storeFlightData.push_back(it->second);
			
			it++;
		}

		return storeFlightData;

	}

	float FindAverageCostOfAllTrips()
	{
		map<string, Flight>::iterator it = FlightDb.begin();

		float avgTripCost = 0.0;
		while(it != FlightDb.end())
		{
			avgTripCost += it->second.airFare;
			it++;
		}
		avgTripCost /= FlightDb.size();
		return  avgTripCost;
	}

	float FindMinFareBetweenCities(string city1, string city2)
	{
		vector<float> storeFare;
		
		map<string, Flight>::iterator it = FlightDb.begin();

		while(it != FlightDb.end())
		{	
			if( it->second.oCity.compare(city1) == 0 
			&& it->second.dCity.compare(city2) == 0 )
			{
				storeFare.push_back(it->second.airFare);
			}
			
			it++;
		}

		if(storeFare.size() > 0)
		{
			sort(storeFare.begin(), storeFare.end(), less<float>());
			return storeFare[0];
		}	
		else
			return 0.0;
	}

	float FindMaxFareByOperator(string airOp)
	{
		vector<float> storeFare;
		
		map<string, Flight>::iterator it = FlightDb.begin();

		while(it != FlightDb.end())
		{
			Flight tempFDetails = it->second;
			if( it->second.airOp.compare(airOp) == 0 )
				storeFare.push_back(it->second.airFare);
			
			it++;
		}

		sort(storeFare.begin(), storeFare.end(), greater<float>());

		return storeFare.at(0);
	}

	void UpdateFareByOperator(string airOp)
	{
		map<string, Flight>::iterator it = FlightDb.begin();

		while(it != FlightDb.end())
		{
			if( it->second.airOp.compare(airOp) == 0 )
			{
				it->second.airFare +=  100;
				printFlightDetails(it->second); 
			}

			it++;
		}
	}

	int getSize() const
	{
		return FlightDb.size();
	}
	
public:
	map<string, Flight> FlightDb;
};



int main()
{
	FlightDataBase FlightDb;

	while(true)
	{
		cout << "<========== Choose Below Options ==================>" << endl;
		cout<< "1.AddTrip" << endl << "2.removeTrip" << endl << "3.updateFareByTrip" << endl
			<< "4.DisplayAllTrips" << endl << "5.FindFlightByNumber" << endl 
			<< "6.FindFlightsByOriginCity" << endl << "7.FindCostOfAllTrips" << endl
			<< "8.FindMinFareBetweenCities" << endl << "9.FindMaxFareByOperator" << endl
			<< "10.UpdateFareByOperator" << endl;
			
		int c;
		cout << "Enter your option: " << endl;
		cin >> c;
		switch(c)
		{
			case 1:
			{
				FlightDb.AddTrip("AI-135", "Bengaluru", "Pune", 3550.00, "AirIndia");
				FlightDb.AddTrip("AA2653", "Bengaluru", "Hyderabad", 4500.00, "AirAsia");
				FlightDb.AddTrip("J543", "Mumbai", "Vizag", 5550.00, "JetAirWays");
				FlightDb.AddTrip("AAI-56", "Delhi", "Bengaluru", 2300.00, "AirAsiaIndia");
				FlightDb.AddTrip("GA-234", "Bengaluru", "Delhi", 8550.00, "GoAir");
				FlightDb.AddTrip("SJ-567", "Noida", "Chennai", 7550.00, "SpiceJet");
				FlightDb.AddTrip("V-135", "Chennai", "Pune", 4550.00, "Vistara");
				FlightDb.AddTrip("IA-675", "Pune", "Bengaluru", 3850.00, "IndianAirlines");
				FlightDb.AddTrip("J543", "Kolkatha", "Pune", 9550.00, "JetAirWays");
				FlightDb.AddTrip("AAI-58", "Pune", "Delhi", 2300.00, "AirAsiaIndia");
				FlightDb.AddTrip("GA-234", "Bengaluru", "Delhi", 8550.00, "GoAir");
				FlightDb.AddTrip("SJ-567", "Hyderabad", "Chennai", 7550.00, "SpiceJet");
				FlightDb.AddTrip("V-135", "Hyderabad", "Pune", 4550.00, "Vistara");
			}
			break;
			case 2:
			{
				string tripName = "";
				cout << "Enter trip to remove: " << endl;
				cin >> tripName;
				cout << " Removing " << tripName << "  Trip" << endl;
				if(FlightDb.getSize() > 0)
					FlightDb.removeTrip(tripName);
				else
					cout << "There are no trips to remove" << endl;
			}
			break; 
			case 3:
			{	

				string  flightNum;
				float fare;
				cout << " Enter Flight Number :" << endl;
				cin >> flightNum;
				cout << " Enter Fare: " << endl;
				cin >> fare;
				cout << "<---------------Updated Trip By Fare ----------->" << endl;
				if(FlightDb.getSize() > 0)
					FlightDb.UpdateFareByTrip(flightNum, fare);
				else
					cout << "No trips to update" << endl;
			}
			break;
			case 4:
			{
				cout << "<-----------------------Display All Trips ------------------->" << endl;
				if(FlightDb.getSize() > 0)
					FlightDb.DisplayAllTrips();
				else
					cout << "No Trips to Display" << endl;
			}
			break;
			case 5:
			{
				string flightNumber;
				cout << "Enter Flight Number: " << endl;
				cin >> flightNumber;
				cout << "<------------------Find Flight By Number "<< flightNumber << "----------->" <<endl;
				Flight flData;
				shared_ptr<Flight> flPtr(new Flight());
				if(FlightDb.getSize() > 0)
				{
					flData = FlightDb.FindFlightByNumber(flightNumber);
					flPtr->printFlightDetails(flData);
				}
				else
					cout << "No Trips to find. please add trips to find" << endl;
			}
			break;
			case 6:
			{
				string oCity;
				cout << "Enter Origin City: " << endl;
				cin >> oCity;
				cout << " <----------------find flight by origin City" << oCity << "--------------->" << endl;
				vector<Flight> FlightDataByOriginCity;
				if(FlightDb.getSize() > 0)
				{
					FlightDataByOriginCity = FlightDb.FindFlightsByOriginCity(oCity);
				}
				else
					cout << "No Trips to find. Please add trips to find" << endl;

				cout << "Printing All flights by origin city  " << endl;
				for(auto it: FlightDataByOriginCity)
					it.printFlightDetails(it);
			}
			break;
			case 7:
			{
				cout << "Average Cost of all trips "<< endl; 
				if(FlightDb.getSize() > 0)
				{
					cout << FlightDb.FindAverageCostOfAllTrips() << endl;
				}
				else
					cout << "There are no trips" << endl;

			}
			break;
			case 8:
			{
				string oCity, dCity;
				cout << "Enter Origin City: " << endl;
				cin >> oCity;
				cout << "Enter Dest City: " << endl;
				cin >> dCity;

				cout << "<------------------find min fare between cities--------------> " << endl;
				cout << "--------> " <<oCity <<" to " << dCity <<" <--------------"<< endl;
				if(FlightDb.getSize() > 0)
				{
					cout << FlightDb.FindMinFareBetweenCities(oCity, dCity) << endl;
				}
				else
					cout << "There are no trips to find. please add trips" << endl;
			}
			break;
			case 9:
			{
				string airOperator;
				cout << "Enter Operator : " << endl;
				cin >> airOperator;
				cout << "<------------------find max fare by Operator "<< airOperator << "-----------------> " << endl;
				if(FlightDb.getSize() > 0)
				{
					cout << FlightDb.FindMaxFareByOperator(airOperator) << endl;
				}
				else
					cout << "There are no trips to find. please add trips" << endl;
			}
			break;
			case 10:
			{
				string airOperator;
				cout << "Enter Operator : " << endl;
				cin >> airOperator;
				cout << "<------------------update fare 100 rs by Operator " << airOperator << "-----------------> " << endl;
				if(FlightDb.getSize() > 0)
				{
					FlightDb.UpdateFareByOperator(airOperator);
					FlightDb.DisplayAllTrips();
				}
				else
					cout << "There are no trips to find. Please add trips" << endl;
			}
			break;
			default:
				cout << "invalid input" << endl;
		}
	}

return 0;
}	