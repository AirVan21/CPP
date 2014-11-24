class String
{
public:
	// Constructor with default value == ""
	String(const char *word = "");
	String(const String &word);
	~String();
	String &operator=(const char *word);
	String &operator=(const String &word);
	String &operator+=(const String &word);
	void print();
private:
	char *pString;
	int mLength;

};