namespace Logger 
{
	void Log(const std::string& message)
	{
		// ここではコンソールにログを出力する例を示します
		// 実際の実装では、ファイルに書き込むなど、他の方法も考えられます
		std::cout << message << std::endl;
	}
}