#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <msclr\marshal_cppstd.h>
#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <iterator>
#include <string.h>
#include <chrono>

namespace Project7 {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	// initialize variables
	map<string, vector<vector<string>>> data;
	string stock; //= input search box
	int days = 7; //=days chosen from button int
	int algoOption = 0; //default to mergeSort = 0, Priority queue = 1
	int dataType = 4; //default to stock close data - 4
	int time = 0; //timer


	//operators used to help the priority queues sort based on the double in the pair
	struct greaterPC {
		constexpr bool operator()(pair<string, double> const& pairA, pair<string, double> const& pairB) const noexcept
		{
			return pairA.second > pairB.second;
		}
	};

	struct lessPC {
		const bool operator()(pair<string, double> const& pairA, pair<string, double> const& pairB) const noexcept
		{
			return pairA.second < pairB.second;
		}
	};

	//Implementation of a min priority queue to get K Largest

	vector<pair<string, double>> KthLargest(vector<pair<string, double>>& _dates, int k)
	{
		auto start = chrono::high_resolution_clock::now();
		
		priority_queue<pair<string, double>, vector<pair<string, double>>, greaterPC> pq;
		for (pair<string, double> i : _dates)
		{
			if (pq.size() > k && i.second < pq.top().second)
				continue;
			pq.push(i);
			if (pq.size() > k)
				pq.pop();
		}

		vector<pair<string, double>> kValues;

		while (!pq.empty())
		{
			kValues.push_back(pq.top());
			pq.pop();
		}
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		//std::cout << duration.count() << endl;
		time += duration.count();
		
		return kValues;
	}

	//Implementation of a max priority queue to get K smallest

	vector<pair<string, double>> KthSmallest(vector<pair<string, double>>& _dates, int k)
	{
		auto start = chrono::high_resolution_clock::now();

		priority_queue<pair<string, double>, vector<pair<string, double>>, lessPC> pq;
		for (pair<string, double> i : _dates)
		{
			if (pq.size() > k && i.second > pq.top().second)
				continue;
			pq.push(i);
			if (pq.size() > k)
				pq.pop();
		}

		vector<pair<string, double>> kValues;

		while (!pq.empty())
		{
			kValues.push_back(pq.top());
			pq.pop();
		}

		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		//std::cout << duration.count() << endl;
		time += duration.count();

		return kValues;
	}

	//Merge subfunction used in merge sort

	void Merge(vector<pair<string, double>>& _piece, int _start, int _mid, int _end)
	{
		int sOne = _mid + 1 - _start;
		int sTwo = _end - _mid;
		vector<pair<string, double>> leftCopy;
		vector<pair<string, double>> rightCopy;

		for (int i = 0; i < sOne; i++) {
			leftCopy.push_back(_piece[_start + i]);
		}

		for (int i = 0; i < sTwo; i++) {
			rightCopy.push_back(_piece[_mid + i + 1]);
		}
		int i = 0;
		int j = 0;
		int k = _start;

		while (i < leftCopy.size() && j < rightCopy.size())
		{
			if (leftCopy[i].second <= rightCopy[j].second) {
				_piece[k] = leftCopy[i];
				i++;
			}
			else {
				_piece[k] = rightCopy[j];
				j++;
			}
			k++;
		}

		while (i < leftCopy.size())
		{
			_piece[k] = leftCopy[i];
			i++;
			k++;
		}

		while (j < rightCopy.size())
		{
			_piece[k] = rightCopy[j];
			j++;
			k++;
		}
	}

	//MergeSort function. Can be used to get k largest or k smallest by finding
	//the first k values or last k values in the sorted vector.

	void MergeSort(vector<pair<string, double>>& _data, int start, int end)
	{
		if (start < end) {
			int mid = (start + end) / 2;
			MergeSort(_data, start, mid);
			MergeSort(_data, mid + 1, end);

			Merge(_data, start, mid, end);
		}
		else {

			return;
		}
	}
	
	void HeapSort(vector<pair<string, double>>& _data)
	{
		priority_queue<pair<string, double>, vector<pair<string, double>>, greaterPC> pq;

		int size = _data.size();

		for (int i = 0; i < size; i++)
		{
			pq.push(_data.back());
			_data.pop_back();
		}

		for (int j = 0; j < size; j++) {
			_data.push_back(pq.top());
			pq.pop();
		}
	}	


	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{

			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::TextBox^ backdrop;
	private: System::Windows::Forms::TextBox^ searchBar;
	private: System::Windows::Forms::TextBox^ peak;
	private: System::Windows::Forms::PictureBox^ leftBackground;
	private: System::Windows::Forms::PictureBox^ rightBackground;
	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::ComboBox^ optionMenu;
	private: System::Windows::Forms::Button^ loadButton;
	private: System::Windows::Forms::PictureBox^ ellipses;
	private: System::Windows::Forms::PictureBox^ checkmark;
	private: System::Windows::Forms::TextBox^ trough;
	private: System::Windows::Forms::TextBox^ name;
	private: System::Windows::Forms::TextBox^ nameText;
	private: System::Windows::Forms::TextBox^ peak2;
	private: System::Windows::Forms::TextBox^ peak3;
	private: System::Windows::Forms::TextBox^ trough1;
	private: System::Windows::Forms::TextBox^ trough2;
	private: System::Windows::Forms::TextBox^ trough3;
	private: System::Windows::Forms::RadioButton^ mergeButton;
	private: System::Windows::Forms::RadioButton^ pqButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ timerLabel;
	private: System::Windows::Forms::Button^ sevenButton;
	private: System::Windows::Forms::Button^ thirtyButton;
	private: System::Windows::Forms::Button^ threehButton;
	private: System::Windows::Forms::Button^ allstoredButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ dayLabel;
	private: System::Windows::Forms::RadioButton^ heapButton;
	private: System::Windows::Forms::TextBox^ peak1;
	private: System::Windows::Forms::Label^ label2;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->backdrop = (gcnew System::Windows::Forms::TextBox());
			this->searchBar = (gcnew System::Windows::Forms::TextBox());
			this->peak = (gcnew System::Windows::Forms::TextBox());
			this->leftBackground = (gcnew System::Windows::Forms::PictureBox());
			this->rightBackground = (gcnew System::Windows::Forms::PictureBox());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->optionMenu = (gcnew System::Windows::Forms::ComboBox());
			this->loadButton = (gcnew System::Windows::Forms::Button());
			this->ellipses = (gcnew System::Windows::Forms::PictureBox());
			this->checkmark = (gcnew System::Windows::Forms::PictureBox());
			this->trough = (gcnew System::Windows::Forms::TextBox());
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->nameText = (gcnew System::Windows::Forms::TextBox());
			this->peak2 = (gcnew System::Windows::Forms::TextBox());
			this->peak3 = (gcnew System::Windows::Forms::TextBox());
			this->trough1 = (gcnew System::Windows::Forms::TextBox());
			this->trough2 = (gcnew System::Windows::Forms::TextBox());
			this->trough3 = (gcnew System::Windows::Forms::TextBox());
			this->mergeButton = (gcnew System::Windows::Forms::RadioButton());
			this->pqButton = (gcnew System::Windows::Forms::RadioButton());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timerLabel = (gcnew System::Windows::Forms::Label());
			this->sevenButton = (gcnew System::Windows::Forms::Button());
			this->thirtyButton = (gcnew System::Windows::Forms::Button());
			this->threehButton = (gcnew System::Windows::Forms::Button());
			this->allstoredButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->dayLabel = (gcnew System::Windows::Forms::Label());
			this->heapButton = (gcnew System::Windows::Forms::RadioButton());
			this->peak1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->leftBackground))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rightBackground))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ellipses))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->checkmark))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &MyForm::folderBrowserDialog1_HelpRequest);
			// 
			// backdrop
			// 
			this->backdrop->BackColor = System::Drawing::SystemColors::WindowText;
			this->backdrop->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->backdrop->Location = System::Drawing::Point(624, 75);
			this->backdrop->Multiline = true;
			this->backdrop->Name = L"backdrop";
			this->backdrop->ReadOnly = true;
			this->backdrop->Size = System::Drawing::Size(858, 607);
			this->backdrop->TabIndex = 0;
			// 
			// searchBar
			// 
			this->searchBar->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(505) {
				L"A", L"AAL", L"AAP", L"AAPL",
					L"ABBV", L"ABC", L"ABT", L"ACN", L"ADBE", L"ADI", L"ADM", L"ADP", L"ADS", L"ADSK", L"AEE", L"AEP", L"AES", L"AET", L"AFL", L"AGN",
					L"AIG", L"AIV", L"AIZ", L"AJG", L"AKAM", L"ALB", L"ALGN", L"ALK", L"ALL", L"ALLE", L"ALXN", L"AMAT", L"AMD", L"AME", L"AMG",
					L"AMGN", L"AMP", L"AMT", L"AMZN", L"ANDV", L"ANSS", L"ANTM", L"AON", L"AOS", L"APA", L"APC", L"APD", L"APH", L"APTV", L"ARE",
					L"ARNC", L"ATVI", L"AVB", L"AVGO", L"AVY", L"AWK", L"AXP", L"AYI", L"AZO", L"BA", L"BAC", L"BAX", L"BBT", L"BBY", L"BDX", L"BEN",
					L"BF.B", L"BHF", L"BHGE", L"BIIB", L"BK", L"BLK", L"BLL", L"BMY", L"BRK.B", L"BSX", L"BWA", L"BXP", L"C", L"CA", L"CAG", L"CAH",
					L"CAT", L"CB", L"CBG", L"CBOE", L"CBS", L"CCI", L"CCL", L"CDNS", L"CELG", L"CERN", L"CF", L"CFG", L"CHD", L"CHK", L"CHRW", L"CHTR",
					L"CI", L"CINF", L"CL", L"CLX", L"CMA", L"CMCSA", L"CME", L"CMG", L"CMI", L"CMS", L"CNC", L"CNP", L"COF", L"COG", L"COL", L"COO",
					L"COP", L"COST", L"COTY", L"CPB", L"CRM", L"CSCO", L"CSRA", L"CSX", L"CTAS", L"CTL", L"CTSH", L"CTXS", L"CVS", L"CVX", L"CXO",
					L"D", L"DAL", L"DE", L"DFS", L"DG", L"DGX", L"DHI", L"DHR", L"DIS", L"DISCA", L"DISCK", L"DISH", L"DLR", L"DLTR", L"DOV", L"DPS",
					L"DRE", L"DRI", L"DTE", L"DUK", L"DVA", L"DVN", L"DWDP", L"DXC", L"EA", L"EBAY", L"ECL", L"ED", L"EFX", L"EIX", L"EL", L"EMN",
					L"EMR", L"EOG", L"EQIX", L"EQR", L"EQT", L"ES", L"ESRX", L"ESS", L"ETFC", L"ETN", L"ETR", L"EVHC", L"EW", L"EXC", L"EXPD", L"EXPE",
					L"EXR", L"F", L"FAST", L"FB", L"FBHS", L"FCX", L"FDX", L"FE", L"FFIV", L"FIS", L"FISV", L"FITB", L"FL", L"FLIR", L"FLR", L"FLS",
					L"FMC", L"FOX", L"FOXA", L"FRT", L"FTI", L"FTV", L"GD", L"GE", L"GGP", L"GILD", L"GIS", L"GLW", L"GM", L"GOOG", L"GOOGL", L"GPC",
					L"GPN", L"GPS", L"GRMN", L"GS", L"GT", L"GWW", L"HAL", L"HAS", L"HBAN", L"HBI", L"HCA", L"HCN", L"HCP", L"HD", L"HES", L"HIG",
					L"HII", L"HLT", L"HOG", L"HOLX", L"HON", L"HP", L"HPE", L"HPQ", L"HRB", L"HRL", L"HRS", L"HSIC", L"HST", L"HSY", L"HUM", L"IBM",
					L"ICE", L"IDXX", L"IFF", L"ILMN", L"INCY", L"INFO", L"INTC", L"INTU", L"IP", L"IPG", L"IQV", L"IR", L"IRM", L"ISRG", L"IT", L"ITW",
					L"IVZ", L"JBHT", L"JCI", L"JEC", L"JNJ", L"JNPR", L"JPM", L"JWN", L"K", L"KEY", L"KHC", L"KIM", L"KLAC", L"KMB", L"KMI", L"KMX",
					L"KO", L"KORS", L"KR", L"KSS", L"KSU", L"L", L"LB", L"LEG", L"LEN", L"LH", L"LKQ", L"LLL", L"LLY", L"LMT", L"LNC", L"LNT", L"LOW",
					L"LRCX", L"LUK", L"LUV", L"LYB", L"M", L"MA", L"MAA", L"MAC", L"MAR", L"MAS", L"MAT", L"MCD", L"MCHP", L"MCK", L"MCO", L"MDLZ",
					L"MDT", L"MET", L"MGM", L"MHK", L"MKC", L"MLM", L"MMC", L"MMM", L"MNST", L"MO", L"MON", L"MOS", L"MPC", L"MRK", L"MRO", L"MS",
					L"MSFT", L"MSI", L"MTB", L"MTD", L"MU", L"MYL", L"NAVI", L"NBL", L"NCLH", L"NDAQ", L"NEE", L"NEM", L"NFLX", L"NFX", L"NI", L"NKE",
					L"NLSN", L"NOC", L"NOV", L"NRG", L"NSC", L"NTAP", L"NTRS", L"NUE", L"NVDA", L"NWL", L"NWS", L"NWSA", L"O", L"OKE", L"OMC", L"ORCL",
					L"ORLY", L"OXY", L"PAYX", L"PBCT", L"PCAR", L"PCG", L"PCLN", L"PDCO", L"PEG", L"PEP", L"PFE", L"PFG", L"PG", L"PGR", L"PH", L"PHM",
					L"PKG", L"PKI", L"PLD", L"PM", L"PNC", L"PNR", L"PNW", L"PPG", L"PPL", L"PRGO", L"PRU", L"PSA", L"PSX", L"PVH", L"PWR", L"PX",
					L"PXD", L"PYPL", L"QCOM", L"QRVO", L"RCL", L"RE", L"REG", L"REGN", L"RF", L"RHI", L"RHT", L"RJF", L"RL", L"RMD", L"ROK", L"ROP",
					L"ROST", L"RRC", L"RSG", L"RTN", L"SBAC", L"SBUX", L"SCG", L"SCHW", L"SEE", L"SHW", L"SIG", L"SJM", L"SLB", L"SLG", L"SNA", L"SNI",
					L"SNPS", L"SO", L"SPG", L"SPGI", L"SRCL", L"SRE", L"STI", L"STT", L"STX", L"STZ", L"SWK", L"SWKS", L"SYF", L"SYK", L"SYMC", L"SYY",
					L"T", L"TAP", L"TDG", L"TEL", L"TGT", L"TIF", L"TJX", L"TMK", L"TMO", L"TPR", L"TRIP", L"TROW", L"TRV", L"TSCO", L"TSN", L"TSS",
					L"TWX", L"TXN", L"TXT", L"UA", L"UAA", L"UAL", L"UDR", L"UHS", L"ULTA", L"UNH", L"UNM", L"UNP", L"UPS", L"URI", L"USB", L"UTX",
					L"V", L"VAR", L"VFC", L"VIAB", L"VLO", L"VMC", L"VNO", L"VRSK", L"VRSN", L"VRTX", L"VTR", L"VZ", L"WAT", L"WBA", L"WDC", L"WEC",
					L"WFC", L"WHR", L"WLTW", L"WM", L"WMB", L"WMT", L"WRK", L"WU", L"WY", L"WYN", L"WYNN", L"XEC", L"XEL", L"XL", L"XLNX", L"XOM",
					L"XRAY", L"XRX", L"XYL", L"YUM", L"ZBH", L"ZION", L"ZTS"
			});
			this->searchBar->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->searchBar->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->searchBar->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
			this->searchBar->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->searchBar->Location = System::Drawing::Point(28, 389);
			this->searchBar->MaxLength = 6;
			this->searchBar->Name = L"searchBar";
			this->searchBar->Size = System::Drawing::Size(367, 36);
			this->searchBar->TabIndex = 2;
			// 
			// peak
			// 
			this->peak->BackColor = System::Drawing::SystemColors::Desktop;
			this->peak->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->peak->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->peak->ForeColor = System::Drawing::Color::White;
			this->peak->Location = System::Drawing::Point(644, 203);
			this->peak->Name = L"peak";
			this->peak->ReadOnly = true;
			this->peak->Size = System::Drawing::Size(144, 43);
			this->peak->TabIndex = 12;
			this->peak->Text = L"PEAKS";
			this->peak->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// leftBackground
			// 
			this->leftBackground->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"leftBackground.BackgroundImage")));
			this->leftBackground->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"leftBackground.Image")));
			this->leftBackground->Location = System::Drawing::Point(0, 0);
			this->leftBackground->Name = L"leftBackground";
			this->leftBackground->Size = System::Drawing::Size(500, 948);
			this->leftBackground->TabIndex = 17;
			this->leftBackground->TabStop = false;
			// 
			// rightBackground
			// 
			this->rightBackground->BackColor = System::Drawing::Color::Transparent;
			this->rightBackground->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"rightBackground.Image")));
			this->rightBackground->Location = System::Drawing::Point(551, 31);
			this->rightBackground->Name = L"rightBackground";
			this->rightBackground->Size = System::Drawing::Size(995, 885);
			this->rightBackground->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->rightBackground->TabIndex = 18;
			this->rightBackground->TabStop = false;
			// 
			// searchButton
			// 
			this->searchButton->BackColor = System::Drawing::Color::Transparent;
			this->searchButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"searchButton.BackgroundImage")));
			this->searchButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->searchButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->searchButton->FlatAppearance->BorderSize = 0;
			this->searchButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"searchButton.Image")));
			this->searchButton->Location = System::Drawing::Point(417, 377);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(64, 61);
			this->searchButton->TabIndex = 19;
			this->searchButton->UseVisualStyleBackColor = false;
			this->searchButton->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
			// 
			// optionMenu
			// 
			this->optionMenu->BackColor = System::Drawing::SystemColors::HighlightText;
			this->optionMenu->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->optionMenu->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->optionMenu->ForeColor = System::Drawing::SystemColors::WindowText;
			this->optionMenu->FormattingEnabled = true;
			this->optionMenu->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Open", L"Close", L"High", L"Low", L"Volume" });
			this->optionMenu->Location = System::Drawing::Point(274, 389);
			this->optionMenu->Name = L"optionMenu";
			this->optionMenu->Size = System::Drawing::Size(121, 36);
			this->optionMenu->TabIndex = 21;
			// 
			// loadButton
			// 
			this->loadButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->loadButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loadButton->Location = System::Drawing::Point(28, 31);
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(105, 41);
			this->loadButton->TabIndex = 22;
			this->loadButton->Text = L"Load";
			this->loadButton->UseVisualStyleBackColor = false;
			this->loadButton->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// ellipses
			// 
			this->ellipses->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ellipses.BackgroundImage")));
			this->ellipses->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ellipses.Image")));
			this->ellipses->Location = System::Drawing::Point(151, 31);
			this->ellipses->Name = L"ellipses";
			this->ellipses->Size = System::Drawing::Size(50, 41);
			this->ellipses->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ellipses->TabIndex = 23;
			this->ellipses->TabStop = false;
			// 
			// checkmark
			// 
			this->checkmark->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"checkmark.BackgroundImage")));
			this->checkmark->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"checkmark.Image")));
			this->checkmark->Location = System::Drawing::Point(151, 22);
			this->checkmark->Name = L"checkmark";
			this->checkmark->Size = System::Drawing::Size(50, 50);
			this->checkmark->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->checkmark->TabIndex = 24;
			this->checkmark->TabStop = false;
			this->checkmark->Visible = false;
			// 
			// trough
			// 
			this->trough->BackColor = System::Drawing::SystemColors::Desktop;
			this->trough->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->trough->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->trough->ForeColor = System::Drawing::Color::White;
			this->trough->Location = System::Drawing::Point(644, 470);
			this->trough->Name = L"trough";
			this->trough->ReadOnly = true;
			this->trough->Size = System::Drawing::Size(166, 43);
			this->trough->TabIndex = 25;
			this->trough->Text = L"TROUGHS";
			// 
			// name
			// 
			this->name->BackColor = System::Drawing::SystemColors::Desktop;
			this->name->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->name->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->name->ForeColor = System::Drawing::Color::White;
			this->name->Location = System::Drawing::Point(644, 97);
			this->name->Name = L"name";
			this->name->ReadOnly = true;
			this->name->Size = System::Drawing::Size(144, 43);
			this->name->TabIndex = 26;
			this->name->Text = L"NAME:";
			// 
			// nameText
			// 
			this->nameText->BackColor = System::Drawing::SystemColors::Desktop;
			this->nameText->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->nameText->ForeColor = System::Drawing::Color::White;
			this->nameText->Location = System::Drawing::Point(768, 97);
			this->nameText->Name = L"nameText";
			this->nameText->ReadOnly = true;
			this->nameText->Size = System::Drawing::Size(144, 50);
			this->nameText->TabIndex = 27;
			this->nameText->Visible = false;
			// 
			// peak2
			// 
			this->peak2->BackColor = System::Drawing::SystemColors::Desktop;
			this->peak2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->peak2->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->peak2->ForeColor = System::Drawing::Color::Lime;
			this->peak2->Location = System::Drawing::Point(816, 279);
			this->peak2->Name = L"peak2";
			this->peak2->ReadOnly = true;
			this->peak2->Size = System::Drawing::Size(584, 43);
			this->peak2->TabIndex = 29;
			// 
			// peak3
			// 
			this->peak3->BackColor = System::Drawing::SystemColors::Desktop;
			this->peak3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->peak3->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->peak3->ForeColor = System::Drawing::Color::Lime;
			this->peak3->Location = System::Drawing::Point(816, 353);
			this->peak3->Name = L"peak3";
			this->peak3->ReadOnly = true;
			this->peak3->Size = System::Drawing::Size(584, 43);
			this->peak3->TabIndex = 30;
			// 
			// trough1
			// 
			this->trough1->BackColor = System::Drawing::SystemColors::Desktop;
			this->trough1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->trough1->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->trough1->ForeColor = System::Drawing::Color::Red;
			this->trough1->Location = System::Drawing::Point(816, 470);
			this->trough1->Name = L"trough1";
			this->trough1->ReadOnly = true;
			this->trough1->Size = System::Drawing::Size(584, 43);
			this->trough1->TabIndex = 33;
			// 
			// trough2
			// 
			this->trough2->BackColor = System::Drawing::SystemColors::Desktop;
			this->trough2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->trough2->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->trough2->ForeColor = System::Drawing::Color::Red;
			this->trough2->Location = System::Drawing::Point(816, 540);
			this->trough2->Name = L"trough2";
			this->trough2->ReadOnly = true;
			this->trough2->Size = System::Drawing::Size(584, 43);
			this->trough2->TabIndex = 32;
			// 
			// trough3
			// 
			this->trough3->BackColor = System::Drawing::SystemColors::Desktop;
			this->trough3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->trough3->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->trough3->ForeColor = System::Drawing::Color::Red;
			this->trough3->Location = System::Drawing::Point(816, 604);
			this->trough3->Name = L"trough3";
			this->trough3->ReadOnly = true;
			this->trough3->Size = System::Drawing::Size(584, 43);
			this->trough3->TabIndex = 31;
			// 
			// mergeButton
			// 
			this->mergeButton->AutoSize = true;
			this->mergeButton->BackColor = System::Drawing::Color::Transparent;
			this->mergeButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mergeButton.BackgroundImage")));
			this->mergeButton->Checked = true;
			this->mergeButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mergeButton->Location = System::Drawing::Point(12, 448);
			this->mergeButton->Name = L"mergeButton";
			this->mergeButton->Size = System::Drawing::Size(138, 28);
			this->mergeButton->TabIndex = 34;
			this->mergeButton->TabStop = true;
			this->mergeButton->Text = L"Merge Sort";
			this->mergeButton->UseVisualStyleBackColor = false;
			this->mergeButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::mergeButton_CheckedChanged);
			// 
			// pqButton
			// 
			this->pqButton->AutoSize = true;
			this->pqButton->BackColor = System::Drawing::Color::Transparent;
			this->pqButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pqButton.BackgroundImage")));
			this->pqButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pqButton->Location = System::Drawing::Point(166, 448);
			this->pqButton->Name = L"pqButton";
			this->pqButton->Size = System::Drawing::Size(171, 28);
			this->pqButton->TabIndex = 35;
			this->pqButton->Text = L"Priority Queue";
			this->pqButton->UseVisualStyleBackColor = false;
			this->pqButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pqButton_CheckedChanged);
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::Transparent;
			this->chart1->BackImage = L"C:\\Users\\Ossedda\\Desktop\\PROJ\\Project7\\Project7\\CHART BACKGROUND.png";
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->ImeMode = System::Windows::Forms::ImeMode::On;
			legend1->Name = L"Price/Amount";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(640, 697);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			this->chart1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->chart1->Size = System::Drawing::Size(400, 190);
			this->chart1->TabIndex = 36;
			this->chart1->Text = L"chart1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label1.Image")));
			this->label1->Location = System::Drawing::Point(1033, 790);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(266, 24);
			this->label1->TabIndex = 37;
			this->label1->Text = L"Time Spent on Algorithm:";
			// 
			// timerLabel
			// 
			this->timerLabel->AutoSize = true;
			this->timerLabel->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->timerLabel->ForeColor = System::Drawing::Color::White;
			this->timerLabel->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"timerLabel.Image")));
			this->timerLabel->Location = System::Drawing::Point(1327, 790);
			this->timerLabel->Name = L"timerLabel";
			this->timerLabel->Size = System::Drawing::Size(52, 24);
			this->timerLabel->TabIndex = 38;
			this->timerLabel->Text = L"0.00";
			// 
			// sevenButton
			// 
			this->sevenButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sevenButton->Location = System::Drawing::Point(28, 540);
			this->sevenButton->Name = L"sevenButton";
			this->sevenButton->Size = System::Drawing::Size(173, 31);
			this->sevenButton->TabIndex = 39;
			this->sevenButton->Text = L"Last 7 Days";
			this->sevenButton->UseVisualStyleBackColor = true;
			this->sevenButton->Click += gcnew System::EventHandler(this, &MyForm::sevenButton_Click);
			// 
			// thirtyButton
			// 
			this->thirtyButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->thirtyButton->Location = System::Drawing::Point(28, 604);
			this->thirtyButton->Name = L"thirtyButton";
			this->thirtyButton->Size = System::Drawing::Size(173, 31);
			this->thirtyButton->TabIndex = 40;
			this->thirtyButton->Text = L"Last 30 Days";
			this->thirtyButton->UseVisualStyleBackColor = true;
			this->thirtyButton->Click += gcnew System::EventHandler(this, &MyForm::thirtyButton_Click);
			// 
			// threehButton
			// 
			this->threehButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->threehButton->Location = System::Drawing::Point(28, 672);
			this->threehButton->Name = L"threehButton";
			this->threehButton->Size = System::Drawing::Size(173, 31);
			this->threehButton->TabIndex = 41;
			this->threehButton->Text = L"Last 300 Days";
			this->threehButton->UseVisualStyleBackColor = true;
			this->threehButton->Click += gcnew System::EventHandler(this, &MyForm::threehButton_Click);
			// 
			// allstoredButton
			// 
			this->allstoredButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->allstoredButton->Location = System::Drawing::Point(28, 738);
			this->allstoredButton->Name = L"allstoredButton";
			this->allstoredButton->Size = System::Drawing::Size(173, 31);
			this->allstoredButton->TabIndex = 42;
			this->allstoredButton->Text = L"All Stored Data";
			this->allstoredButton->UseVisualStyleBackColor = true;
			this->allstoredButton->Click += gcnew System::EventHandler(this, &MyForm::allstoredButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label3.Image")));
			this->label3->Location = System::Drawing::Point(270, 540);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(111, 24);
			this->label3->TabIndex = 43;
			this->label3->Text = L"Data Size:";
			// 
			// dayLabel
			// 
			this->dayLabel->AutoSize = true;
			this->dayLabel->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->dayLabel->ForeColor = System::Drawing::Color::White;
			this->dayLabel->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"dayLabel.Image")));
			this->dayLabel->Location = System::Drawing::Point(303, 604);
			this->dayLabel->Name = L"dayLabel";
			this->dayLabel->Size = System::Drawing::Size(78, 24);
			this->dayLabel->TabIndex = 44;
			this->dayLabel->Text = L"7 Days";
			// 
			// heapButton
			// 
			this->heapButton->AutoSize = true;
			this->heapButton->BackColor = System::Drawing::Color::Transparent;
			this->heapButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"heapButton.BackgroundImage")));
			this->heapButton->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->heapButton->Location = System::Drawing::Point(354, 448);
			this->heapButton->Name = L"heapButton";
			this->heapButton->Size = System::Drawing::Size(127, 28);
			this->heapButton->TabIndex = 45;
			this->heapButton->Text = L"Heap Sort";
			this->heapButton->UseVisualStyleBackColor = false;
			this->heapButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::heapButton_CheckedChanged);
			// 
			// peak1
			// 
			this->peak1->BackColor = System::Drawing::SystemColors::Desktop;
			this->peak1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->peak1->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->peak1->ForeColor = System::Drawing::Color::Lime;
			this->peak1->Location = System::Drawing::Point(816, 203);
			this->peak1->Name = L"peak1";
			this->peak1->ReadOnly = true;
			this->peak1->Size = System::Drawing::Size(584, 43);
			this->peak1->TabIndex = 46;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label2.Image")));
			this->label2->Location = System::Drawing::Point(1084, 814);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(168, 24);
			this->label2->TabIndex = 47;
			this->label2->Text = L"(microseconds)";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1578, 944);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->peak1);
			this->Controls->Add(this->heapButton);
			this->Controls->Add(this->dayLabel);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->allstoredButton);
			this->Controls->Add(this->threehButton);
			this->Controls->Add(this->thirtyButton);
			this->Controls->Add(this->sevenButton);
			this->Controls->Add(this->timerLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pqButton);
			this->Controls->Add(this->mergeButton);
			this->Controls->Add(this->trough1);
			this->Controls->Add(this->trough2);
			this->Controls->Add(this->trough3);
			this->Controls->Add(this->peak3);
			this->Controls->Add(this->peak2);
			this->Controls->Add(this->nameText);
			this->Controls->Add(this->name);
			this->Controls->Add(this->trough);
			this->Controls->Add(this->checkmark);
			this->Controls->Add(this->ellipses);
			this->Controls->Add(this->loadButton);
			this->Controls->Add(this->optionMenu);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->peak);
			this->Controls->Add(this->searchBar);
			this->Controls->Add(this->backdrop);
			this->Controls->Add(this->leftBackground);
			this->Controls->Add(this->rightBackground);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"StockSurvey";
			this->TransparencyKey = System::Drawing::Color::LightSkyBlue;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->leftBackground))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rightBackground))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ellipses))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->checkmark))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void folderBrowserDialog1_HelpRequest(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
		nameText->Visible = true;
		nameText->Text = searchBar->Text;
		string optionCheck = msclr::interop::marshal_as<std::string>(optionMenu->Text);
		stock = msclr::interop::marshal_as<std::string>(searchBar->Text);

		if (optionCheck == "Low") {
			dataType = 1;
		}
		else if (optionCheck == "High") {
			dataType = 2;
		}
		else if (optionCheck == "Open") {
			dataType = 3;
		}
		else if (optionCheck == "Close") {
			dataType = 4;
		}
		else if (optionCheck == "Volume") {
			dataType = 5;
		}

		if (days == -1) {
			days = data[stock].size()-1;
		}

		vector<pair<string, double>> input;
		//std::cout << data[stock].size() - days - 1 << endl;
		for (int i = data[stock].size() - days - 1; i < data[stock].size(); i++) {
			input.push_back(make_pair(data[stock][i][0], stod(data[stock][i][dataType])));
		}

		chart1->Series->Clear();
		chart1->Series->Add("Data");
		chart1->Series["Data"]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
		chart1->Series["Data"]->BorderWidth = 3;
		for (int i = 0; i < input.size(); i++) {
			chart1->Series["Data"]->Points->AddXY(i+1, input[i].second);
		}

		if (algoOption == 0) {
			auto start = chrono::high_resolution_clock::now();

			MergeSort(input, 0, input.size() - 1);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			//std::cout << duration.count() << endl;
			timerLabel->Text = gcnew String(to_string(duration.count()).c_str());

			auto y = trough1->Text;

			string temp = to_string(input[0].second);
			y = gcnew String((temp.substr(0, temp.find(".")+3) + char(9) + input[0].first).c_str());
			trough1->Text = y;

			temp = to_string(input[1].second);
			y = gcnew String((temp.substr(0, temp.find(".")+3) + char(9) + input[1].first).c_str());
			trough2->Text = y;

			temp = to_string(input[2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[2].first).c_str());
			trough3->Text = y;

			temp = to_string(input[input.size() - 1].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 1].first).c_str());
			peak1->Text = y;
			
			temp = to_string(input[input.size() - 2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 2].first).c_str());
			peak2->Text = y;

			temp = to_string(input[input.size() - 3].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 3].first).c_str());
			peak3->Text = y;
		}
		else if (algoOption == 1) { //not else in case we want to implement more sorting methods in the future
			auto top = KthLargest(input, 3);
			auto bot = KthSmallest(input, 3);
			timerLabel->Text = gcnew String(to_string(time).c_str());

			time = 0;
			auto y = trough1->Text;

			string temp = to_string(bot[2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + bot[2].first).c_str());
			trough1->Text = y;

			temp = to_string(bot[1].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + bot[1].first).c_str());
			trough2->Text = y;

			temp = to_string(bot[0].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + bot[0].first).c_str());
			trough3->Text = y;

			temp = to_string(top[2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + top[2].first).c_str());
			peak1->Text = y;

			temp = to_string(top[1].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + top[1].first).c_str());
			peak2->Text = y;

			temp = to_string(top[0].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + top[0].first).c_str());
			peak3->Text = y;

		}
		else if (algoOption == 2) {
			auto start = chrono::high_resolution_clock::now();
			HeapSort(input);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			//std::cout << duration.count() << endl;
			timerLabel->Text = gcnew String(to_string(duration.count()).c_str());

			auto y = trough1->Text;

			string temp = to_string(input[0].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[0].first).c_str());
			trough1->Text = y;

			temp = to_string(input[1].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[1].first).c_str());
			trough2->Text = y;

			temp = to_string(input[2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[2].first).c_str());
			trough3->Text = y;

			temp = to_string(input[input.size() - 1].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 1].first).c_str());
			peak1->Text = y;

			temp = to_string(input[input.size() - 2].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 2].first).c_str());
			peak2->Text = y;

			temp = to_string(input[input.size() - 3].second);
			y = gcnew String((temp.substr(0, temp.find(".") + 3) + char(9) + input[input.size() - 3].first).c_str());
			peak3->Text = y;
		}

	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		//initializing variables and setting up
		this->ellipses->Visible = true;
		string line, date, open, high, low, close, volume, name;
		string inputFile;
		inputFile = "stonks.csv";
		ifstream inFile(inputFile);

		//skip header line
		getline(inFile, line);

		//reading in data from csv file
		while (getline(inFile, line)) {
			vector<string> temp;
			istringstream stream(line);
			getline(stream, date, ',');
			getline(stream, open, ',');
			getline(stream, high, ',');
			getline(stream, low, ',');
			getline(stream, close, ',');
			getline(stream, volume, ',');
			getline(stream, name, ',');

			/*
				date - 0
				open - 1
				high - 2
				low - 3
				close - 4
				volume - 5
			*/
			temp.push_back(date);
			temp.push_back(open);
			temp.push_back(high);
			temp.push_back(low);
			temp.push_back(close);
			temp.push_back(volume);

			data[name].push_back(temp);
		}

		inFile.close();
		this->ellipses->Visible = false;
		this->checkmark->Visible = true;
	}



	private: System::Void mergeButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		algoOption = 0;

	}
	private: System::Void pqButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		algoOption = 1;
	}
	private: System::Void heapButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		algoOption = 2;
	}
private: System::Void sevenButton_Click(System::Object^ sender, System::EventArgs^ e) {
	days = 7;
	dayLabel->Text = "7 Days";
}
private: System::Void thirtyButton_Click(System::Object^ sender, System::EventArgs^ e) {
	days = 30;
	dayLabel->Text = "30 Days";
}
private: System::Void threehButton_Click(System::Object^ sender, System::EventArgs^ e) {
	days = 300;
	dayLabel->Text = "300 Days";
}
private: System::Void allstoredButton_Click(System::Object^ sender, System::EventArgs^ e) {
	days = -1;
	dayLabel->Text = "All Days";
}
};
}


