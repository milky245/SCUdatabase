//===----------------------------------------------------------------------===//
//
//
//
// p0_starter.h
//
// Ñ¦ÖÇº­  2019141460081
//
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

//#include "common/exception.h"

namespace scudb {

	/**
	* The Matrix type defines a common
	* interface for matrix operations.
	*/
	template <typename T>
	class Matrix {
	protected:
		/**
		* TODO(P0): Add implementation
		*
		* Construct a new Matrix instance.
		* @param rows The number of rows
		* @param cols The number of columns
		*
		*/
		Matrix(int rows, int cols) 
		{
			rows_ = rows;
			cols_ = cols;
			linear_ = new T[rows*cols];
			//linear_ = (T*)malloc(sizeof(T)*cols*rows);
			memset(linear_, 0, sizeof(T)*rows*cols);
		}

		/** The number of rows in the matrix */
		int rows_;
		/** The number of columns in the matrix */
		int cols_;

		/**
		* TODO(P0): Allocate the array in the constructor.
		* TODO(P0): Deallocate the array in the destructor.
		* A flattened array containing the elements of the matrix.
		*/
		T *linear_;

	public:
		/** @return The number of rows in the matrix */
		virtual int GetRowCount() const = 0;

		/** @return The number of columns in the matrix */
		virtual int GetColumnCount() const = 0;

		/**
		* Get the (i,j)th matrix element.
		*
		* Throw OUT_OF_RANGE if either index is out of range.
		*
		* @param i The row index
		* @param j The column index
		* @return The (i,j)th matrix element
		* @throws OUT_OF_RANGE if either index is out of range
		*/
		virtual T GetElement(int i, int j) const = 0;

		/**
		* Set the (i,j)th matrix element.
		*
		* Throw OUT_OF_RANGE if either index is out of range.
		*
		* @param i The row index
		* @param j The column index
		* @param val The value to insert
		* @throws OUT_OF_RANGE if either index is out of range
		*/
		virtual void SetElement(int i, int j, T val) = 0;

		/**
		* Fill the elements of the matrix from `source`.
		*
		* Throw OUT_OF_RANGE in the event that `source`
		* does not contain the required number of elements.
		*
		* @param source The source container
		* @throws OUT_OF_RANGE if `source` is incorrect size
		*/
		virtual void FillFrom(const std::vector<T> &source) = 0;

		/**
		* Destroy a matrix instance.
		* TODO(P0): Add implementation
		*/
		virtual ~Matrix()
		{
			delete[] linear_;

		}
	};

	/**
	* The RowMatrix type is a concrete matrix implementation.
	* It implements the interface defined by the Matrix type.
	*/
	template <typename T>
	class RowMatrix : public Matrix<T> {
	//private:
		//T** nums;
	public:
		/**
		* TODO(P0): Add implementation
		*
		* Construct a new RowMatrix instance.
		* @param rows The number of rows
		* @param cols The number of columns
		*/
		RowMatrix(int rows, int cols) : Matrix<T>(rows, cols)
		{
			data_ = new T*[rows];
			for (int i = 0; i < Matrix<T>::rows_; i++)
			{
				data_[i] = &this->linear_[i*cols];
			}

		}

		/**
		* TODO(P0): Add implementation
		* @return The number of rows in the matrix
		*/
		int GetRowCount() const override { return Matrix<T>::rows_; }

		/**
		* TODO(P0): Add implementation
		* @return The number of columns in the matrix
		*/
		int GetColumnCount() const override { return Matrix<T>::cols_; }

		/**
		* TODO(P0): Add implementation
		*
		* Get the (i,j)th matrix element.
		*
		* Throw OUT_OF_RANGE if either index is out of range.
		*
		* @param i The row index
		* @param j The column index
		* @return The (i,j)th matrix element
		* @throws OUT_OF_RANGE if either index is out of range
		*/
		T GetElement(int i, int j) const override 
		{
			//throw NotImplementedException{ "RowMatrix::GetElement() not implemented." };
			if (i < 0 || i >= Matrix<T>::rows_
				|| j < 0 || j >= Matrix<T>::cols_)
			{
				printf("crossed the boundary of index");
				return 0;
			}
			else
			{
				return data_[i][j];
			}
		}

		/**
		* Set the (i,j)th matrix element.
		*
		* Throw OUT_OF_RANGE if either index is out of range.
		*
		* @param i The row index
		* @param j The column index
		* @param val The value to insert
		* @throws OUT_OF_RANGE if either index is out of range
		*/
		void SetElement(int i, int j, T val) override
		{
			if (i < 0 || i >= Matrix<T>::rows_
				|| j < 0 || j >= Matrix<T>::cols_)
			{
				printf("crossed the boundary of index");
				return;
			}
			else
			{
				data_[i][j] = val;
				return;
			}
		}

		/**
		* TODO(P0): Add implementation
		*
		* Fill the elements of the matrix from `source`.
		*
		* Throw OUT_OF_RANGE in the event that `source`
		* does not contain the required number of elements.
		*
		* @param source The source container
		* @throws OUT_OF_RANGE if `source` is incorrect size
		*/
		void FillFrom(const std::vector<T> &source) override {
			//throw NotImplementedException{ "RowMatrix::FillFrom() not implemented." };
			for (int i = 0; i < Matrix <T>::rows_; i++)
			{
				for (int j = 0; j < Matrix<T>::cols_; j++)
				{
					data_[i][j] = source[i*this->cols_ + j];
				}
			}
		}
		void ShowMatrix()
		{
			for (int i = 0; i<Matrix<T>::rows_; ++i) {
				for (int j = 0; j<Matrix<T>::cols_; ++j) {
					printf("%d ", data_[i][j]);
				}
				printf("\n");
			}
		}

		/**
		* TODO(P0): Add implementation
		*
		* Destroy a RowMatrix instance.
		*/
		~RowMatrix() override
		{
			delete[] data_;
		}

	private:
		/**
		* A 2D array containing the elements of the matrix in row-major format.
		*
		* TODO(P0):
		* - Allocate the array of row pointers in the constructor.
		* - Use these pointers to point to corresponding elements of the `linear` array.
		* - Don't forget to deallocate the array in the destructor.
		*/
		T **data_;
	};

	/**
	* The RowMatrixOperations class defines operations
	* that may be performed on instances of `RowMatrix`.
	*/
	template <typename T>
	class RowMatrixOperations {
	public:
		/**
		* Compute (`matrixA` + `matrixB`) and return the result.
		* Return `nullptr` if dimensions mismatch for input matrices.
		* @param matrixA Input matrix
		* @param matrixB Input matrix
		* @return The result of matrix addition
		*/
		static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
			// TODO(P0): Add implementation
			if (matrixA->GetRowCount() != matrixB->GetRowCount()
				|| matrixA->GetColumnCount() != matrixB->GetColumnCount())
			{
				return std::unique_ptr<RowMatrix<T>>(nullptr);
			}
			int curRows = matrixA->GetRowCount();
			int curCols = matrixA->GetColumnCount();
			std::unique_ptr<RowMatrix<T>> matrixSum(new RowMatrix<T>(curRows,curCols));
			for (int i = 0; i < curRows; i++)
			{
				for (int j = 0; j < curCols; j++)
				{
					matrixSum->SetElement(i, j, matrixA->GetElement(i, j) + matrixB->GetElement(i, j));
				}
			}
			return matrixSum;
		}

		/**
		* Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
		* Return `nullptr` if dimensions mismatch for input matrices.
		* @param matrixA Input matrix
		* @param matrixB Input matrix
		* @return The result of matrix multiplication
		*/
		static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
			// TODO(P0): Add implementation
			if (matrixA->GetColumnCount() != matrixB->GetRowCount())
			{
				return std::unique_ptr<RowMatrix<T>>(nullptr);
			}
			int ARows = matrixA->GetRowCount();
			int BCols = matrixB->GetColumnCount();
			std::unique_ptr<RowMatrix<T>> matrixProd(new RowMatrix<T>(ARows, BCols));
			for (int i = 0; i < ARows; i++)
			{
				for (int j = 0; j < BCols; j++)
				{
					for (int k = 0; k < matrixA->GetColumnCount(); k++)
					{
						T curNum = matrixB->GetElement(i, j);
						matrixProd->SetElement(i, j, matrixA->GetElement(i, j)*matrixB->GetElement(i, j) + curNum);
					}
				}
			}
			return matrixProd;
		}

		/**
		* Simplified General Matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
		* Return `nullptr` if dimensions mismatch for input matrices.
		* @param matrixA Input matrix
		* @param matrixB Input matrix
		* @param matrixC Input matrix
		* @return The result of general matrix multiply
		*/
		static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB,
			const RowMatrix<T> *matrixC) {
			// TODO(P0): Add implementation
			//return std::unique_ptr<RowMatrix<T>>(nullptr);
			std::unique_ptr<RowMatrix<T>> AmulB = Multiply(matrixA, matrixB);
			if (AmulB->GetRowCount() != matrixC->GetRowCount()
				|| AmulB->GetColumnCount() != matrixC->GetColumnCount())
			{
				return std::unique_ptr<RowMatrix<T>>(nullptr);
			}
			//int rows = AmulB->GetRowCount();
			//int cols = AmulB->GetColumnCount();
			const RowMatrix<T> *temp = AmulB.get();
			AmulB = Add(temp, matrixC);
			//std::unique_ptr<RowMatrix<T>> matrixGemm(new RowMatrix<T>(rows, cols));
			//std::unique_ptr<RowMatrix<T>> matrixGemm = Add(AmulB, matrixC);
			return AmulB;
		}
	};
}  // namespace scudb
