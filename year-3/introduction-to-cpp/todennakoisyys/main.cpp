#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//#include <iostream>
//#include "discretedistribution.h"
//#include "chensamplegenerator.h"
//#include "chisquarecriterion.h"

//using namespace std;

//int main(int argc, char *argv[])
//{
//    vector<Point> points{
//                Point(1, 0.21),
//                Point(2, 0.5),
//                Point(3, 0.14),
//                Point(4, 0.03),
//                Point(5, 0.12)
//    };

//    DiscreteDistribution d1(points);
//    ChenSampleGenerator generator(3);
//    Sample samp = generator.generate(d1, 1000);
//    GroupedSample gSamp = samp.group();

//    for (auto v : gSamp.values())
//        cout << v.value() << ": " << v.count() << endl;

//    for (auto v : generator.generate(d1, 1000).group().values())
//        cout << v.value() << ": " << v.count() << endl;


//    ChiSquareCriterion chisq(d1, gSamp);
//    cout << "degrees: " << chisq.degrees() << endl
//         << "chisq:   " << chisq.chiSquare() << endl
//         << "pValue:  " << chisq.pValue() << endl;

//    return 0;
//}
