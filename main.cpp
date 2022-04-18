#include <iostream>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include<windows.h>
#pragma hdrstop
using namespace std;


void show_gistogram (const auto bins, size_t number_count)
{
    size_t screen_width;
    cerr << "Enter screen width" << endl;
    cin >> screen_width;
    while (screen_width < 7 || screen_width > 80000 || screen_width < number_count/3)
    {
        if (screen_width < 7)
        {
            cerr << "Too less screen width" << endl;
        }
        if (screen_width >80)
        {
            cerr << "Too large screen width" << endl;
        }
        if (screen_width < number_count/3)
        {
            cerr << "its nessesary to be more then 1/3 of number count" << endl;
        }
        cerr << endl;
        cin >> screen_width;

    }


    const size_t max_aster = screen_width - 3 -1;
    size_t max_bin = bins[0];
    for (size_t bin:bins)
    {
        if (max_bin<bin)
        {
            max_bin = bin;
        }
    }



    for (size_t bin : bins)
    {
        size_t hei = bin;
        // нужно ли масштабировать
        if (max_bin > max_aster)
        {
            hei = max_aster * (static_cast<double> (bin) / max_bin);
        }
        if(bin<100)
        {
            cout << " ";
        }
        if (bin<10)
        {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t i = 0; i < hei; i++)
        {
            cout << "*";
        }
        cout << endl;
    }

}

vector <size_t>
make_histogram(size_t bin_count, double max, double min, vector <double> numbers)
{
    vector <size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < size(numbers); i++)
    {
        bool found = false;
        for (size_t j = 0; j < bin_count-1 && !found; j++)
        {
            auto low = min + j * bin_size;
            auto hi = min + ((j + 1) * bin_size);
            if (low <= numbers[i] && hi > numbers[i])
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


vector <double>
input_numbers(size_t count)
{
    vector <double> result(count);
    for (size_t i=0; i<count; i++)
    {
        cerr << i << ")";
        cin >> result[i];
    }
    return result;
}

void
find_minmax (const vector <double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (size_t i=0; i<size(numbers); i++)
    {
        if(numbers[i] > max)
        {
            max = numbers[i];
        }
        if (numbers[i] < min)
        {
            min = numbers[i];
        }
    }

}


void
svg_begin(double width, double height)
 {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}




void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}

void
svg_end()
{
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill){

    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}

void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const string stroke = "black";
    const string fill = "#3CB371";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        const double text_wid= IMAGE_WIDTH-bin_width-30;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#3CB371");
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();
}






int main()
{
    setlocale(LC_ALL, "RU");

    // Ввод данных
    size_t number_count;
    cerr << "Enter number count" << endl;
    cin >> number_count;
    const vector <double>& numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count" << endl;
    cin >> bin_count;
    // Расчет гистограммы
    double min;
    double max;
    find_minmax(numbers, min, max);


    const auto bins = make_histogram(bin_count, max, min, numbers);

    show_histogram_svg(bins);


    //Вывод данных


}
