#include <memory>
#include <stdexcept>
#include <vector>
#include "p0_starter.h"
#include <iostream>
using namespace std;
using namespace scudb;

//TEST FOR P0_STARTER.H

void test()
{
	RowMatrix<int> test(5, 5);
	vector<int> source(25, 1);
	
	cout << "test of FillFrom" << endl;

	test.FillFrom(source);
	cout << "Row num: " << test.GetRowCount() << endl;
	cout << "Column num: " << test.GetColumnCount() << endl;
	test.ShowMatrix();

	cout << "test of SetElement" << endl;
	test.SetElement(2, 2, 0);
	test.ShowMatrix();
	//test.~RowMatrix();
	//system("PAUSE");

	RowMatrix<int> A(3, 3);
	vector<int> srcA(9, 3);
	A.FillFrom(srcA);

	RowMatrix<int> B(3, 3);
	vector<int> srcB(9, 5);
	B.FillFrom(srcB);
	
	RowMatrixOperations<int> opTest;
	//int result;
	std::unique_ptr<RowMatrix<int>> AaddB = opTest.Add(&A, &B);
	cout << "Add result:" << endl;
	AaddB->ShowMatrix();
	cout << "Mul result:" << endl;
	std::unique_ptr<RowMatrix<int>> AmulB = opTest.Multiply(&A, &B);
	AmulB->ShowMatrix();
	cout << "GEMM result:" << endl;
	std::unique_ptr<RowMatrix<int>> AGemB = opTest.GEMM(&A, &B, &A);
	AGemB->ShowMatrix();

}
int main()
{
	test();
	system("PAUSE");
	return 0;
}