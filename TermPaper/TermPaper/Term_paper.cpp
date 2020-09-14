#include<iostream>
#include<Windows.h>
#include <iomanip>
#include<vector>
#include <memory>
#include<fstream>
#include<string>
class Flowers;
using namespace std;

double InputDouble()
{
	double n;
	while (!(cin >> n) || cin.peek() != '\n')
	{
		cin.clear();
		while (cin.get() != '\n')
		{
		}
		cout << "Error,wrong input!\n";
	}
	return n;
}

int InputInt()
{
	double n;
	while (!(cin >> n) || cin.peek() != '\n' || (n - int(n)) != 0)
	{
		cin.clear();
		while (cin.get() != '\n')
		{
		}
		cout << "Error,wrong input!\n";
	}
	return n;
}

template <class T>
struct Status
{
	T* ptr;
	int counter;
};

template <class T>
class SmartPointer
{
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr = 0);
	SmartPointer(const SmartPointer&);
	~SmartPointer();
	SmartPointer& operator=(const SmartPointer&);
	T* operator->() const;
	void showCounter() { cout << smartPtr->counter; }
};

template <class T>
SmartPointer<T>::SmartPointer(T* ptr)
{
	if (!ptr) smartPtr = NULL;
	else
	{
		smartPtr = new Status<T>;
		smartPtr->ptr = ptr;
		smartPtr->counter = 1;
	}
}
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj)
	: smartPtr(obj.smartPtr)
{
	if (smartPtr) smartPtr->counter++;
}


template <class T>
SmartPointer<T>::~SmartPointer()
{
	if (smartPtr)
	{
		smartPtr->counter--;
		if (smartPtr->counter <= 0)
		{

			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
}

template <class T>
T* SmartPointer<T>::operator->() const
{
	if (smartPtr)
	{
		return smartPtr->ptr;
	}
	return NULL;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& obj)
{
	if (smartPtr)
	{
		smartPtr->counter--; // уменьшаем счетчик «прикрепленных»объектов
		if (smartPtr->counter <= 0)
		{
			// если объектов нет, то выполняется освобождается выделенная память
			delete smartPtr->ptr;
			delete smartPtr;
		}
	}
	smartPtr = obj.smartPtr; // присоединение к новому указателю
	if (smartPtr) smartPtr->counter++; // увеличить счетчик	«прикрепленных» объектов
	return *this;
}

class Customer
{
	double Summ = 0;
	string FIO;
	string Phone_number;
public:
	Customer()
	{
	};

	~Customer()
	{
	};
	friend std::ofstream& operator <<(std::ofstream& out, const Customer& customer)
	{
		out << "Имя клиента:" << customer.FIO << " Номер телефона клиента:" << customer.Phone_number << endl;
		return out;
	}
	friend std::istream& operator >> (std::ifstream& in, Customer& customer)
	{
		in >> customer.FIO;
		in >> customer.Phone_number;
	}
	void Set_name()
	{
		system("cls");
		cout << "Введите ФИО:";
		cin.clear();
		cin.ignore();
		getline(cin, FIO);
		cout << "Введите номер телефона:";
		cin.clear();
		cin.ignore();
		getline(cin, Phone_number);
	}

	string Get_name()
	{
		return FIO;
	}

	string Get_Phome()
	{
		return Phone_number;
	}

	double Set_Summ(double WholeSum)
	{
		Summ = WholeSum;
		return Summ;
	}
};




class Flowers
{
	string FlowerName;
	double prise;
	int Kol;
public:
	Flowers() {};

	~Flowers() {};

	friend vector<Flowers> Make_CostomBouq();
	friend ostream operator<<(const ostream& out, const Flowers& flower);
	friend std::ofstream& operator <<(std::ofstream& out, const Flowers& flower)
	{
		out << "Название цветка:" << flower.FlowerName << " Количество:" << flower.Kol << endl;
		return out;
	}
	friend std::istream& operator >> (std::ifstream& in, Flowers& flower)
	{
		in >> flower.FlowerName;
		in >> flower.prise;
	}
	Flowers Set_flower(string Fl_Name, double Prise)
	{
		Flowers flower;
		flower.FlowerName = Fl_Name;
		flower.prise = Prise;
		cout << "Какое колличество цветов " << Fl_Name << " вы хотите заказать?";
		Kol = InputInt();
		std::cout << "В корзину добавлено: " << Kol << " цветов вида " << FlowerName << endl;
		cout << "Их цена :" << Kol * Prise << " бел.р" << endl;
		return flower;
	}

	Flowers Same_Vlower(string Fl_Name, double Prise)
	{
		Flowers flower;
		flower.FlowerName = Fl_Name;
		flower.prise = Prise;
		return flower;
	}

	double Get_Prise(Flowers fl)
	{
		return fl.prise;
	}

	string Get_FlowerName()
	{
		return FlowerName;
	}

	void Create_Flower(string Name, double Prise)
	{
		FlowerName = Name;
		prise = Prise;
	}
};

string ChooseColor()
{
	int key;
	cout << "Выберите цвет:\n 1-Жёлтый\n 2-Розовый\n 3-Красный \n 4-Белый\n 5-Фиолетовый\n";
	key = InputInt();
	try
	{
		while (key < 1 || key > 5)
		{
			cout << "Неверный ввод! Введите число от 1 до 5\n";
			key = InputInt();
		}
		switch (key)
		{
		case 1:
			return "Желтый";
			break;
		case 2:
			return "Розовый";
			break;
		case 3:
			return "Красный";
			break;
		case 4:
			return "Белый";
			break;
		case 5:
			return "Фиолетовый";
			break;
		}
	}
	catch (...)
	{
		cout << "Неверный ввод!\n";
	}
}


vector<Flowers> Make_CostomBouq()
{
	string color;
	const string FlowerName[12] = {
		"Астра", "Гвоздика", "Гортензия", "Ирис", "Ландыш", "Лилия", "Нарцис", "Пион", "Роза", "Хризантема", "Лаванда",
		"Тюльпан"
	};
	const double FlowerCost[12] = { 2.5, 2.5, 6, 2, 2, 5, 2.7, 5, 4, 2, 2, 3 };
	vector<Flowers> Flower;
	cout << "------------ Создание собственного букета ------------\n";
	Flowers Fl;
	int no, key;
	do
	{
		cout << "Выберите вид цветов для добавления в букет:\n";
		cout <<
			"1-Астра (2.5 р)\n2-Гвоздика (2.5 р)\n3-Гортензия (6 р)\n4-Ирис (2 р)\n5-Ландыш (2 р)\n6-Лилия (5 р)\n7-Нарцис(2.7 р)\n8-Пион (5 р)\n9-Роза (4 р)\n10-Хризантема (2 р)\n11-Лаванда (2 р)\n12-Тюльпан (3 р)\n";
		try {
			no = InputInt();
		}
		catch (...)
		{
			cout << "Неверный ввод!";
		}
		while (no < 1 || no > 12)
		{
			no = InputInt();
			cout << "Неверный ввод! Введите число от 1 до 12\n";
		}
		color = ChooseColor();
		Flower.push_back(Fl.Set_flower(FlowerName[no - 1], FlowerCost[no - 1]));
		for (int j = 1; j < Fl.Kol; j++)
		{
			Flower.push_back(Fl.Same_Vlower(FlowerName[no - 1], FlowerCost[no - 1]));
		}
		cout << "Добавить ёще вид цветов?\n1-Да\n2-Нет\n";
		key = InputInt();
	} while (key != 2);

	return Flower;
}

double Whole_Summ(vector<Flowers> OrderedFlowers)
{
	double Summ = 0;
	for (int i = 0; i < OrderedFlowers.size(); i++)
	{
		Summ += OrderedFlowers[i].Get_Prise(OrderedFlowers[i]);
	}
	return Summ;
}

void WriteInFile(Customer Cli, vector<Flowers> Vec)
{
	fstream File;
	string name, txt = ".txt", Name;
	Name = Cli.Get_name() + txt;
	int kol = 1;
	File.open(Name, fstream::in | fstream::out | fstream::trunc);
	File << "---------------Данные по заказу клиента---------------\n";
	File << "Имя клиента:" << Cli.Get_name() << endl;
	File << "Телефон клиента:" << Cli.Get_Phome() << endl;
	File << "----------------------Детали заказа---------------------" << endl;
	File << "| Название | Количество | Цена за штуку | Общая стоимость |" << endl;
	for (int i = 0; i < Vec.size(); i++)
	{
		if (i != Vec.size() - 1)
		{
			if (Vec[i].Get_FlowerName() == Vec[i + 1].Get_FlowerName())
			{
				kol++;
			}
			else
			{
				File << "|" << setw(15) << Vec[i].Get_FlowerName() << "|" << setw(10) << kol << "|" << Vec[i].
					Get_Prise(Vec[i]) << "|" << Vec[i].Get_Prise(Vec[i]) * kol << "|" << endl;
				kol = 1;
			}
		}
		else
		{
			File << "|" << setw(15) << Vec[i].Get_FlowerName() << "|" << setw(10) << kol << "|" << Vec[i].
				Get_Prise(Vec[i]) << "|" << Vec[i].Get_Prise(Vec[i]) * kol << "|" << endl;
			kol = 1;
		}
	}
	File << "--------------------------------------------------------\n";
	File << "Вся сумма заказа:" << Whole_Summ(Vec) << "бел.руб";
	File.close();
}

class FlowerOrder : public Flowers, public Customer
{
	Customer Costom;
	vector<Flowers> Flow;
	vector<FlowerOrder> Bouqet;
	string BoquetName;
	double BoquetCost;
	double WholeSumm;

public:
	vector<FlowerOrder> PremadeBouqet();
	friend double Whole_Summ(vector<Flowers> OrderedFlowers);
	friend double Whole_Summ(vector<FlowerOrder> Boquet);
	friend void WriteInFile(Customer Cli, vector<Flowers> Vec);
	friend void WriteInFile(Customer Cli, vector<FlowerOrder> Vec);

	FlowerOrder()
	{
	};

	~FlowerOrder()
	{
	};

	void Fill_Form(vector<string>* Filenames)
	{
		int key, l;
		double summ;
		Costom.Set_name();
		Filenames->push_back(Costom.Get_name());
		fstream File(Costom.Get_name() + ".txt");
		cout << Costom.Get_name() << " ,хотите выбрать букет из готовых или собрать самостоятельно?" << endl;

		cout << "1-Собрать самостоятельно\n2-Выбрать из готовых\n";
		key = InputInt();
		switch (key)
		{
		case 1:
			Flow = Make_CostomBouq();
			summ = Whole_Summ(Flow);
			cout << "Полная сумма заказа:" << summ << "бел.р" << endl;
			Costom.Set_Summ(summ);
			WriteInFile(Costom, Flow);
			break;
		default: case 2:
			Bouqet = PremadeBouqet();
			summ = Whole_Summ(Bouqet);
			cout << "Полная сумма заказа:" << summ << "бел.р" << endl;
			Costom.Set_Summ(summ);
			WriteInFile(Costom, Bouqet);
			break;
		}

		while (1)
		{
			if (key == 1)
			{
				Correct();
			}
			else
			{
				CorrectBouqet();
			}
			int ans;
			cout << "Завершить изменения?\n1-Да\n2-Нет\n";
			ans = InputInt();
			if (ans == 1)
				break;
		}
		ReadFile(&File);
	}

	void Set_BouqetName(string name)
	{
		BoquetName = name;
	}

	void Set_Cost(double cost)
	{
		BoquetCost = cost;
	}

	double Get_BoquePrise(FlowerOrder Prise)
	{
		return BoquetCost;
	}

	string Get_BoqueName()
	{
		return BoquetName;
	}

	void Correct()
	{
		int i, j, menu = 1;
		double summ;
		vector<Flowers> fl;
		fl = Flow;

		fstream File(Costom.Get_name() + ".txt");
		File.open(Costom.Get_name() + ".txt", fstream::in | fstream::out | fstream::app);
		cout << "Хотите изменить заказ?\n1-Да\n2-Нет\n";
		i = InputInt();
		switch (i)
		{
		case 1:
			cout << "1-Удалить цветы\n2-Добавить цветы\n3-Просмотреть заказ\n";
			j = InputInt();
			switch (j)
			{
			case 1:
				Flow = Delete(Costom, fl);
				summ = Whole_Summ(Flow);
				cout << "Полная сумма заказа:" << summ << "бел.р" << endl;
				Costom.Set_Summ(summ);
				WriteInFile(Costom, Flow);
				break;
			case 2:
				Flow = Add(Costom, fl);
				summ = Whole_Summ(Flow);

				cout << "Полная сумма заказа:" << summ << "бел.р" << endl;
				Costom.Set_Summ(summ);
				WriteInFile(Costom, Flow);
				break;
			default: case 3:

				ReadFile1();
				break;
			}


		case 2:
			return;
			break;
		}
	}

	vector<Flowers> Delete(Customer Cli, vector<Flowers> Fl)
	{
		vector<Flowers> fl;
		fl = Fl;
		fstream File;
		string str;
		string Name, txt = ".txt";
		Name = Cli.Get_name() + txt;
		const string FlowerName[12] = {
			"Астра", "Гвоздика", "Гортензия", "Ирис", "Ландыш", "Лилия", "Нарцис", "Пион", "Роза", "Хризантема",
			"Лаванда", "Тюльпан"
		};
		int i, kol;
		cout << "Какой вид цветов вы хотите удалить?\n";
		cout <<
			"1-Астра (2.5 р)\n2-Гвоздика (2.5 р)\n3-Гортензия (6 р)\n4-Ирис (2 р)\n5-Ландыш (2 р)\n6-Лилия (5 р)\n7-Нарцис(2.7 р)\n8-Пион (5 р)\n9-Роза (4 р)\n10-Хризантема (2 р)\n11-Лаванда (2 р)\n12-Тюльпан (3 р)\n";
		i = InputInt();
		str = FlowerName[i - 1];
		cout << "Какое кол-во цветов этого вида нужно удалить?" << endl;
		kol = InputInt();
		File.open(Name, fstream::in | fstream::out | fstream::app);
		for (int j = 0; j < fl.size(); j++)
		{
			if (fl[j].Get_FlowerName() == str && kol > 0)
			{
				fl.erase(fl.begin() + j);
				j--;
				kol--;
			}
		}
		File.close();
		return fl;
	}

	vector<FlowerOrder> Delete(Customer Cli, vector<FlowerOrder> Ord)
	{
		vector<FlowerOrder> Order;
		Order = Ord;
		int i, kol;
		fstream File;
		string str, Name, txt = ".txt";
		Name = Cli.Get_name() + txt;
		string BoquetName[5] = {
			"Букет№1(30 р):\nПионов-7шт,Роз-5шт,Лилии-3шт\n", "Букет№2(35 р):\nРоз-11шт,Гортензии-3шт,Хризантемы-6шт\n",
			"Букет№3(40 р):\nИрис-5шт,Лилия-6шт,Напцис-6шт\n",
			"Букет№4(35 р)\nГортензия-3шт,Тюльпан-5шт,Хризантема-5шт\n",
			"Букет№5(30 р):\nЛаванда-7шт,Ирис-5шт\n"
		};
		cout << "Какой букет вы хотите удалить?\n";
		for (int i = 0; i < 5; i++)
		{
			cout << BoquetName[i] << endl;
		}
		i = InputInt();
		str = BoquetName[i - 1];
		cout << "Какое кол-во букетов этого вида нужно удалить?" << endl;
		kol = InputInt();
		File.open(Name, fstream::in | fstream::out | fstream::app);
		for (int j = 0; j < Order.size(); j++)
		{
			if (Order[j].Get_BoqueName() == str && kol > 0)
			{
				Order.erase(Order.begin() + j);
				j--;
				kol--;
			}
		}
		File.close();
		return Order;
	}

	vector<Flowers> Add(Customer Cli, vector<Flowers> Fl)
	{
		fstream File;
		string str, Name, txt = ".txt";
		Name = Cli.Get_name() + txt;
		Flowers Flower;
		int i, kol;
		const string FlowerName[12] = {
			"Астра", "Гвоздика", "Гортензия", "Ирис", "Ландыш", "Лилия", "Нарцис", "Пион", "Роза", "Хризантема",
			"Лаванда", "Тюльпан"
		};
		const double FlowerCost[12] = { 2.5, 2.5, 6, 2, 2.7, 5, 3, 5, 4, 2, 2, 3 };
		cout << "Какой вид цветов вы хотите добавить?\n";
		cout <<
			"1-Астра (2.5 р)\n2-Гвоздика (2.5 р)\n3-Гортензия (6 р)\n4-Ирис (2 р)\n5-Ландыш (2 р)\n6-Лилия (5 р)\n7-Нарцис(2.7 р)\n8-Пион (5 р)\n9-Роза (4 р)\n10-Хризантема (2 р)\n11-Лаванда (2 р)\n12-Тюльпан (3 р)\n";
		i = InputInt();
		while (i < 1 || i > 12)
		{
			cout << "Неыерный ввод! Введите число от 1 до 12!\n";
			i = InputInt();
		}
		str = FlowerName[i - 1];
		cout << "Какое кол-во цветов этого вида нужно добавить?" << endl;
		kol = InputInt();
		File.open(Name, fstream::in | fstream::out | fstream::app);
		for (int j = 0; j < kol; j++)
		{
			Flower.Create_Flower(str, FlowerCost[i - 1]);
			Fl.push_back(Flower);
		}
		File.close();
		return Fl;
	}

	vector<FlowerOrder> Add(Customer Cli, vector<FlowerOrder> Ord)
	{
		fstream File;
		string str, Name, txt = ".txt";
		Name = Cli.Get_name() + txt;
		FlowerOrder Bouqet;
		int i, kol;
		string BoquetName[5] = {
			"Букет№1(30 р):\nПионов-7шт,Роз-5шт,Лилии-3шт\n", "Букет№2(35 р):\nРоз-11шт,Гортензии-3шт,Хризантемы-6шт\n",
			"Букет№3(40 р):\nИрис-5шт,Лилия-6шт,Напцис-6шт\n",
			"Букет№4(35 р)\nГортензия-3шт,Тюльпан-5шт,Хризантема-5шт\n",
			"Букет№5(30 р):\nЛаванда-7шт,Ирис-5шт\n"
		};
		double BoquetCost[5] = { 30, 35, 40, 35, 30 };
		cout << "Какой букет вы хотите добавить?\n";
		for (int i = 0; i < 5; i++)
		{
			cout << BoquetName[i] << endl;
		}
		i = InputInt();
		while (i < 1 || i > 5)
		{
			cout << "Неыерный ввод! Введите число от 1 до 5!\n";
			i = InputInt();
		}
		str = BoquetName[i - 1];
		cout << "Какое кол-во букетов этого вида нужно добавить?" << endl;
		kol = InputInt();
		File.open(Name, fstream::in | fstream::out | fstream::app);
		for (int j = 0; j < kol; j++)
		{
			Bouqet.Set_BouqetName(str);
			Bouqet.Set_Cost(BoquetCost[i - 1]);
			Ord.push_back(Bouqet);
		}
		File.close();
		return Ord;
	}

	void CorrectBouqet()
	{
		double summ;
		int i, j;
		vector<FlowerOrder> Bo;
		Bo = Bouqet;
		//Bouqet.clear();
		cout << "Хотите изменить заказ?\n1-Да\n2-Нет\n";
		i = InputInt();
		while (i != 1 || i != 2)
		{
			cout << "Неверный ввод! Введите 1 или 2!\n";
			i = InputInt();
		}
		fstream File(Costom.Get_name() + ".txt");
		switch (i)
		{
		case 1:
			cout << "1-Удалить цветы\n2-Добавить цветы\n";
			j = InputInt();
			while (j != 1 || j != 2)
			{
				cout << "Неверный ввод! Введите 1 или 2!\n";
				j = InputInt();
			}
			switch (j)
			{
			case 1:
				Bouqet = Delete(Costom, Bo);
				summ = Whole_Summ(Bouqet);
				Costom.Set_Summ(summ);
				WriteInFile(Costom, Bouqet);
				system("CLS");
				ReadFile1();

				break;
			case 2:
				Bouqet = Add(Costom, Bo);
				summ = Whole_Summ(Bouqet);
				Costom.Set_Summ(summ);
				WriteInFile(Costom, Bouqet);
				system("CLS");
				ReadFile1();

				break;
			}
		case 2:
			break;
		}
	}

	void ReadFile(fstream* File)
	{
		system("CLS");
		string txt = ".txt";
		string Name = Costom.Get_name() + txt;
		File->open(Name, fstream::in | fstream::out);
		string line;
		while (getline(*File, line))
		{
			cout << line << endl;
		}
		File->close();
	}

	void ReadFile1()
	{
		system("CLS");
		fstream File;
		string txt = ".txt";
		string Name = Costom.Get_name() + txt;
		File.open(Name, fstream::in | fstream::out | fstream::app);
		string line;
		while (getline(File, line))
		{
			cout << line << endl;
		}
		File.close();
	}
};

void WriteInFile(Customer Cli, vector<FlowerOrder> Vec)
{
	fstream File;
	string name, Name, txt = ".txt";
	Name = Cli.Get_name() + txt;
	File.open(Name, fstream::in | fstream::out | fstream::trunc);
	File << "---------------Данные по заказу клиента---------------\n";
	File << "Имя клиента:" << Cli.Get_name() << endl;
	File << "Телефон клиента:" << Cli.Get_Phome() << endl;
	File << "---------------------Детали заказа--------------------" << endl;
	for (int i = 0; i < Vec.size(); i++)
	{
		File << Vec[i].Get_BoqueName() << " цена: " << Vec[i].Get_BoquePrise(Vec[i]) << "бел.руб" << endl;
	}
	File << "--------------------------------------------------------\n";
	File << "Вся сумма заказа:" << Whole_Summ(Vec) << "бел.руб\n";
	File.close();
}

double Whole_Summ(vector<FlowerOrder> Boquet)
{
	double Summ = 0;
	for (int i = 0; i < Boquet.size(); i++)
	{
		Summ += Boquet[i].Get_BoquePrise(Boquet[i]);
	}
	return Summ;
}

vector<FlowerOrder> FlowerOrder::PremadeBouqet()
{
	string BoquetName[5] = {
		"Букет№1(30 р):\nПионов-7шт,Роз-5шт,Лилии-3шт\n", "Букет№2(35 р):\nРоз-11шт,Гортензии-3шт,Хризантемы-6шт\n",
		"Букет№3(40 р):\nИрис-5шт,Лилия-6шт,Напцис-6шт\n", "Букет№4(35 р)\nГортензия-3шт,Тюльпан-5шт,Хризантема-5шт\n",
		"Букет№5(30 р):\nЛаванда-7шт,Ирис-5шт\n"
	};
	double BoquetCost[5] = { 30, 35, 40, 35, 30 };
	vector<FlowerOrder> Bouqet;
	FlowerOrder Boq;
	int kol, No;
	cout << "------------ Выбор букета из готовых ------------\n";
	cout << "Какаое кол-во букетов вы хотите заказать?" << endl;
	kol = InputInt();
	for (int i = 0; i < kol; i++)
	{
		cout << "Букет для добавления:\n" << endl;
		for (int i = 0; i < 5; i++)
		{
			cout << BoquetName[i] << endl;
		}
		No = InputInt();
		while (No < 1 || No > 5)
		{
			cout << "Неверный ввод! Введите число от 1 до 5!\n";
			No = InputInt();
		}
		Boq.Set_BouqetName(BoquetName[No - 1]);
		Boq.Set_Cost(BoquetCost[No - 1]);
		Bouqet.push_back(Boq);
	}
	return Bouqet;
}

string encryptDecrypt(string toEncrypt) {
	char key[3] = { 'K', 'C', 'Q' };
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}
int Auto()
{
	string ra, login, pass, rpass, rlogin, clogin, cpass;
	cout << "Добро пожаловать!" << endl << "Регистрация/Авторизация(r/a): ";
	cin >> ra;
	if (ra == "r")
	{
		cout << "Логин: ";
		cin >> rlogin;
		cout << "Пароль: ";
		cin >> rpass;
		rpass = encryptDecrypt(rpass);
		ofstream flogin("login.txt");
		flogin << rlogin;
		flogin.close();
		ofstream fpass("pass.txt");
		fpass << rpass;
		fpass.close();
		cout << "Регистрация прошла успешно!\n";
		return 4;
	};
	if (ra == "a")
	{
		cout << "...чтение..." << endl;
		ifstream flogin("login.txt");
		ifstream fpass("pass.txt");
		while (!flogin.eof() & !fpass.eof())
		{
			flogin >> clogin;
			fpass >> cpass;
			cpass = encryptDecrypt(cpass);
		};
		cout << "Логин: ";
		cin >> login;
		cout << "Пароль: ";
		cin >> pass;
		fpass.close();
		flogin.close();
		if (login == "Admin" && login == clogin & pass == cpass)
		{
			return 2;
		}
		if (login == clogin & pass == cpass)
		{
			cout << "Готово!" << endl;
			return 1;
		}
		else if (login != clogin)
		{
			cerr << "Ошибка: неверный логин" << endl;
			return 3;
		}
		else if (pass != cpass)
		{
			cerr << "Ошибка: неверный пароль" << endl;
			return 3;
		};
	};
	if (ra != "a" & ra != "r")
	{
		cerr << "Неверный ввод!" << endl;
		system("pause");
	};

	system("pause");
}

fstream NewFileForSave(vector<string> Filenames)
{
	//функция записи в файл имён заказчиков 
	fstream FileForSave;
	FileForSave.open("ClientNames.txt", fstream::in | fstream::out | fstream::trunc);
	if (FileForSave.is_open())
	{
		for (int i = 0; i < Filenames.size(); i++)
		{
			FileForSave << Filenames[i] << "\n";
		}
	}
	else
	{
		cout << "Ошибка открытия!";
	}
	FileForSave.close();
	return FileForSave;
}

fstream AddFileForSave(vector<string> Filenames)
{
	//функция записи в файл имён заказчиков 
	fstream FileForSave;
	FileForSave.open("ClientNames.txt", fstream::in | fstream::out | fstream::app);
	if (FileForSave.is_open())
	{
		for (int i = 0; i < Filenames.size(); i++)
		{
			FileForSave << Filenames[i] << "\n";
		}
	}
	else
	{
		cout << "Ошибка открытия!";
	}
	FileForSave.close();
	return FileForSave;
}

vector<string> LoadFilenames(string Name)
{
	//загрузка имён файлов из файла
	fstream FileForLoand;
	vector<string> Filenames;
	string name;
	FileForLoand.open(Name, fstream::in | fstream::out | fstream::app);
	while (!FileForLoand.eof())
	{
		while (getline(FileForLoand, name))
		{
			Filenames.push_back(name);
		}
	}
	FileForLoand.close();
	return Filenames;
}

fstream FileForSave(vector<string> Filenames)
{
	//функция записи в файл имён заказчиков 
	fstream FileForSave;
	FileForSave.open("ClientNames.txt", fstream::in | fstream::out | fstream::trunc);
	if (FileForSave.is_open())
	{
		for (int i = 0; i < Filenames.size(); i++)
		{
			FileForSave << Filenames[i] << "\n";
		}
	}
	else
	{
		cout << "Ошибка открытия!";
	}
	FileForSave.close();
	return FileForSave;
}

vector<string> RemoveFile(vector<string> FileName)
{
	string File;
	char filename;
	string txt = ".txt";
	string Name;
	cout << "Введите имя пользователя для выполнения его заказа:" << endl;
	cin.clear();
	cin.ignore();
	getline(cin, File);
	for (int i = 0; i < FileName.size(); i++)
	{
		if (FileName[i] == File)
		{
			Name = FileName[i] + txt;
			remove(Name.c_str());
			cout << "Файл удалён\n";
			FileName.erase(FileName.begin() + i);
		}
	}
	return FileName;
}

void ShowFile(vector<string> FileNames)
{
	//функция для вывода информации по заказу
	string name, Name;
	string txt = ".txt";

	vector<string> str;
	cout << "Введите имя заказчика:";
	cin.clear();
	cin.ignore();
	getline(cin, name);
	Name = name + txt;
	for (int i = 0; i < FileNames.size(); i++)
	{
		if (FileNames[i] == name)
		{
			str = LoadFilenames(Name);
		}
	}
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i] << endl;
	}
}

class Admin : public FlowerOrder
{
public:
	virtual void FileForSave(vector<string> Filenames) = 0;
	virtual void ShowFile(vector<string> FileNames) = 0;
	virtual void RemoveFile(vector<string> FileName) = 0;
	virtual void NewFileForSave(vector<string> Filenames) = 0;
};
template<typename T>
class FlowerShop : public FlowerOrder, public Admin
{
private:
	T CompOrders;
	T ResOrders;
public:
	void OrdersComp()
	{
		T Orders;
		T kol = 0;
		Orders = LoadFilenames("ClientNames.txt");
		kol = Orders.size();
		cout << "Заказов в обработке " << kol;
	}
};
int main()
{
	int a, key = 1;
	vector<string> ClientNames;
	fstream FileSave;
	SmartPointer<FlowerOrder> Orde(new FlowerOrder);
	int ordernumbers = 0;
	do
	{
		a = Auto();
		if (a == 2 || a == 1)
			break;
	} while (a == 4 || a != 5 || a != 2);
	switch (a)
	{
	default: case 1:
		system("cls");
		cout << "Вы вошли как пользователь!\n";
		Orde->Fill_Form(&ClientNames);
		FileSave = AddFileForSave(ClientNames);
		break;
	case 2:
		system("cls");
		cout << "Вы вошли как Администратор!\n";
		while (key != 0)
		{
			ClientNames = LoadFilenames("ClientNames.txt");
			cout << "------------------------------------------------\n";
			cout << " 1-Вывести информацию по заказу клиента\n 2-Выполнить заказ\n 3-Удалить заказ\n 0-Выйти\n";
			cout << "------------------------------------------------\n";
			key = InputInt();
			switch (key)
			{
			case 1:
				for (int i = 0; i < ClientNames.size(); i++)
				{
					cout << ClientNames[i] << "\n";
				}
				ShowFile(ClientNames);
				break;
			case 2:
				for (int i = 0; i < ClientNames.size(); i++)
				{
					cout << ClientNames[i] << "\n";
				}
				ClientNames = RemoveFile(ClientNames);
				FileSave = FileForSave(ClientNames);
				for (int i = 0; i < ordernumbers; i++)
				{
					cout << ClientNames[i] << "\n";
				}
				break;
			case 3:
				for (int i = 0; i < ClientNames.size(); i++)
				{
					cout << ClientNames[i] << "\n";
				}
				ClientNames = RemoveFile(ClientNames);
				FileSave = FileForSave(ClientNames);
				for (int i = 0; i < ordernumbers; i++)
				{
					cout << ClientNames[i] << "\n";
				}
				break;
			default: case 0:
				break;
			}
		}
		return 0;
	}

}
