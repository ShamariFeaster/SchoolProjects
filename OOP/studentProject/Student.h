class Student
{
public:
	Student();
	Student(const char* fn, const char* ln);
	virtual void compute();
	virtual void PrintRow();
	void PrintGrade();
	const char * GetCourse();
	void PrintName();
protected:
	char* first;
	char* last;
	char* course;
	double final_avg;
	
	
};

class English: public Student
{
public:
	English();
	English(const char* fn, const char* ln, int att, int p, int m, int f);
	void compute();
	void PrintRow();
private:
	int attendance;
	int project;
	int midterm;
	int final;
	
	//grade weighting
	double a_weight;
	double p_weight;
	double m_weight;
	double f_weight;
};

class History: public Student
{
public:
	History();
	History(const char* fn, const char* ln, int tp, int mt, int f);
	void compute();
	void PrintRow();
private:
	int term_paper;
	int midterm;
	int final;
	
	//grade weighting
	double t_weight;
	double m_weight;
	double f_weight;
};

class Math: public Student
{
public:
	Math();
	Math(const char* fn, const char* ln, int q1, int q2, int q3, int q4, int q5, int t1, int t2, int f);
	void compute();
	void PrintRow();
private:
	double q_avg;
	int q1, q2, q3, q4, q5;
	int test1, test2;
	int final;
	
	//grade weighting
	double q_weight;
	double t1_weight;
	double t2_weight;
	double f_weight;
};
	
