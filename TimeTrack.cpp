// TimeTrack.cpp : Defines the entry point for the console application.

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include <boost\date_time\gregorian\gregorian.hpp>

#include <boost\filesystem\path.hpp>
#include <boost\filesystem\operations.hpp>
#include <boost\filesystem\fstream.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
namespace bfs = boost::filesystem;
namespace bg = boost::gregorian;

//return STRING containing logging START time
std::string log_Start(std::string & timeType)
{
	using namespace std::chrono;

	system_clock::time_point t = system_clock::now();
	time_t time = system_clock::to_time_t(t);

	std::string start = "Time Type: ";
	start += timeType + " START Time: " + ctime(&time);
	return start;
}

//return STRING containing logging STOP time
std::string log_Stop(std::string & timeType)
{
	using namespace std::chrono;

	system_clock::time_point t = system_clock::now();
	time_t time = system_clock::to_time_t(t);

	std::string stop = "Time Type: ";
	stop += timeType + " STOP Time: " + ctime(&time);
	return stop;
}

//create directory & today's log file
void create_Project(bfs::path &root, std::string &today)
{
	bfs::path dir = root / today;
	bfs::path filename = today + ".txt";
	if (!bfs::exists(dir)) bfs::create_directory(dir); //(root / today)) bfs::create_directory(root / today);
	if (!bfs::exists(dir / filename))
	{
		bfs::ofstream file(dir / filename);
		file.close();
	}
}

//write the log line to today's log file
void write_Log(bfs::path &root, std::string &today, std::string &logLine)
{
	bfs::path dir = root / today;
	bfs::path filename = today + ".txt";
	if (!bfs::exists(dir / filename)) return;
	
	bfs::ofstream file(dir / filename);
	file << logLine << endl;
	file.close();
	return;
}

int main()
{
	std::string timeType = "", logging = "", start = "", stop = "", logLine = "";
	
	//use boost::gregorian to construct today's date in ISO Extended format
	bg::date date(bg::day_clock::local_day());
	std::string today(bg::to_iso_extended_string(date));
	std::cout << "Today's date is " << today << endl;

	//use boost::filesystem to define a root path
	bfs::path root = "C:/Dev/test/";
	
	std::cout << "Hello, this is the Time Tracker app!" << endl << "This will be your time tracker that will write a time to a file. Would you like to log a time? Y/N" << endl;
	std::getline(std::cin, logging);
	
	//create directory with today's date if no directory exists for today's logging
	if (logging == "Y") create_Project(root, today);

	while (logging == "Y")
	{
		std::cout << "What type of time would you like to log?: " << endl;
		std::getline(std::cin, timeType);
		std::cout << "The type of time you will be logging is: " << timeType << endl;
		start = log_Start(timeType);
		std::cout << start << endl;

		std::cout << "Please enter any string to STOP logging..." << endl;
		std::getline(std::cin, logging);
		stop = log_Stop(timeType);
		std::cout << stop << endl;

		logLine = start + " " + stop;
		std::cout << logLine;
		write_Log(root, today, logLine);

		std::cout << "Would you like to continue logging time? Y/N" << endl;
		std::getline(std::cin, logging);
	}

    return 0;
}