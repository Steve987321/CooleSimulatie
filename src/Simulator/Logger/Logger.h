#pragma once

namespace sim
{

class logger
{
private:
	std::shared_mutex m_mutex;
	HANDLE m_hOutput;

	std::string get_time() const 
	{
		std::ostringstream ss;
		std::string time;

		auto t = std::time(NULL);
		tm newtime;
		localtime_s(&newtime, &t);

		ss << std::put_time(&newtime, "%H:%M:%S");
		return ss.str();
	}
public:
	inline enum class log_type
	{
		LOK = 10,	    // green
		LERROR = 12,	// red
		LDEBUG = 9,		// blue
		LWARNING = 14	// yellow
	};

	logger() 
	{
		m_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	template <typename ... args> 
	void Print(log_type type, args... Args)
	{
		std::unique_lock<std::shared_mutex> lock(m_mutex);

		SetConsoleTextAttribute(m_hOutput, (WORD)type);

		const char* logtypec;
		std::string time = get_time();

		switch (type)
		{
		case log_type::LDEBUG:
			logtypec = "[.]";
			break;
		case log_type::LERROR:
			logtypec = "[-]";
			break;
		case log_type::LOK:
			logtypec = "[+]";
			break;
		case log_type::LWARNING:
			logtypec = "[!]";
			break;
		default:
			logtypec = "??????????????????????????????";
			break;

		}

		std::cout << logtypec << ' ';

		SetConsoleTextAttribute(m_hOutput, 8); // white

		std::cout << time << ' ';

		if (type != log_type::LDEBUG) SetConsoleTextAttribute(m_hOutput, 15);

		printf(Args..., Args...);
		std::cout << std::endl;
	}
	
};

}

inline auto p_logger = std::make_unique<sim::logger>();
#define log_Ok(msg, ...) p_logger->Print(sim::logger::log_type::LOK, msg, __VA_ARGS__); 
#define log_Debug(msg, ...) p_logger->Print(sim::logger::log_type::LDEBUG, msg, __VA_ARGS__); 
#define log_Error(msg, ...) p_logger->Print(sim::logger::log_type::LERROR, msg, __VA_ARGS__); 
#define log_Warn(msg, ...) p_logger->Print(sim::logger::log_type::LWARNING, msg, __VA_ARGS__); 