#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Matrix/Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Matrix01_Init)
		{
			// TODO: Your test code here
			bool hasException = false;
			try
			{
				mango::Matrix mex(3, 2, 0);
			}
			catch (std::length_error& ex)
			{
				hasException = true;
			}
			Assert::IsTrue(hasException);



			unsigned rows = 3;
			unsigned cols = 2;
			unsigned pages = 4;

			mango::Matrix m1(3, 2);

			Assert::AreEqual(m1.Rows(), rows);
			Assert::AreEqual(m1.Cols(), cols);
			Assert::AreEqual(m1.Pages(), unsigned(1));

			mango::Matrix m2(rows, cols, pages);
			Assert::AreEqual(m2.Pages(), pages);

			for (unsigned row = 0; row < rows; row++)
			{
				for (unsigned col = 0; col < cols; col++)
				{
					for (unsigned page = 0; page < pages; page++)
					{
						Assert::AreEqual(m2(row, col, page), 0.0f, 0.0001f);
					}
				}
			}
		}

		TEST_METHOD(Matrix02_ElementAsignment)
		{
			mango::Matrix m(2, 3);

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 1; k++)
					{
						m(i, j, k) = i + j + k + 0.001f;
					}
				}
			}



			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::AreEqual(m(i, j), i + j + 0.001f, 0.0001f);
				}
			}
		}

		TEST_METHOD(Matrix03_Index)
		{
			mango::Matrix m(2, 3, 4);

			bool exThron = false;
			try
			{
				float a = m(2, 2, 1);
			}
			catch (std::out_of_range& ex)
			{
				exThron = true;
			}
			Assert::IsTrue(exThron);
		}


		TEST_METHOD(Matrix03_OperatorEqual)
		{
			mango::Matrix m1(3, 4, 2);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						m1(row, col, page) = row + col + page;
					}
				}
			}

			mango::Matrix m2(1, 9);
			m2 = m1;
			Assert::AreEqual(m2.Rows(), m1.Rows());
			Assert::AreEqual(m2.Cols(), m1.Cols());
			Assert::AreEqual(m2.Pages(), m1.Pages());


			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m2(row, col, page), m1(row, col, page), 0.00001f);
					}
				}
			}

			mango::Matrix m3(1, 1);
			m3 = std::move(m2);
			Assert::AreEqual(m3.Rows(), m1.Rows());
			Assert::AreEqual(m3.Cols(), m1.Cols());
			Assert::AreEqual(m3.Pages(), m1.Pages());
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m3(row, col, page), m1(row, col, page), 0.00001f);
					}
				}
			}

		}

		TEST_METHOD(Matrix04_OperatorWithMatrix)
		{
			mango::Matrix m1(3, 4, 2);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						m1(row, col, page) = 1;
					}
				}
			}

			mango::Matrix m2(3, 4, 2);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						m2(row, col, page) = 2;
					}
				}
			}

			mango::Matrix m3 = m1 + m2;
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m3(row, col, page), 3.0f, 0.0001f);
					}
				}
			}


			////////////////////////////////////////////////////////////////////
			mango::Matrix a1(1, 1, 1);
			for (unsigned row = 0; row < a1.Rows(); row++)
			{
				for (unsigned col = 0; col < a1.Cols(); col++)
				{
					for (unsigned page = 0; page < a1.Pages(); page++)
					{
						a1(row, col, page) = 1;
					}
				}
			}

			mango::Matrix a2(2, 3, 4);
			for (unsigned row = 0; row < a2.Rows(); row++)
			{
				for (unsigned col = 0; col < a2.Cols(); col++)
				{
					for (unsigned page = 0; page < a2.Pages(); page++)
					{
						a2(row, col, page) = 2;
					}
				}
			}

			mango::Matrix a3 = a1 + a2;

			Assert::AreEqual(a3.Rows(), 2u);
			Assert::AreEqual(a3.Cols(), 3u);
			Assert::AreEqual(a3.Pages(), 4u);


			for (unsigned row = 0; row < a3.Rows(); row++)
			{
				for (unsigned col = 0; col < a3.Cols(); col++)
				{
					for (unsigned page = 0; page < a3.Pages(); page++)
					{
						Assert::AreEqual(a3(row, col, page), 3.0f, 0.00001f);
					}
				}
			}





		}


		TEST_METHOD(Matrix05_CopyConstruction)
		{
			mango::Matrix m1(3, 4, 2);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						m1(row, col, page) = row + col + page;
					}
				}
			}

			mango::Matrix m2(m1 + m1);
			Assert::AreEqual(m2.Rows(), 3u);
			Assert::AreEqual(m2.Cols(), 4u);
			Assert::AreEqual(m2.Pages(), 2u);

			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m2(row, col, page), float(row + col + page) * 2, 0.00001f);
					}
				}
			}


			mango::Matrix m3(m1);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m3(row, col, page), float(row + col + page), 0.00001f);
					}
				}
			}

			mango::Matrix m4;
			mango::Matrix m5(m4);
			mango::Matrix m6(std::move(m3));
			Assert::AreEqual(m3.Rows(), 0u);
			Assert::AreEqual(m3.Cols(), 0u);
			Assert::AreEqual(m3.Pages(), 0u);

		}

		TEST_METHOD(Matrix06_AllNoLessThan)
		{
			float threshold = 2;
			mango::Matrix m(3, 4);
			m.AllNoLessThan(threshold);

			for (unsigned row = 0; row < m.Rows(); row++)
			{
				for (unsigned col = 0; col < m.Cols(); col++)
				{
					Assert::IsTrue(m(row, col) >= threshold);
				}
			}
		}


		TEST_METHOD(Matrix07_Log)
		{
			mango::Matrix m(2, 3, 2);



			for (unsigned row = 0; row < m.Rows(); row++)
			{
				for (unsigned col = 0; col < m.Cols(); col++)
				{
					for (unsigned page = 0; page < m.Pages(); page++)
					{
						m(row, col, page) = row + col + page + 1;
					}
				}
			}


			mango::Matrix m2 = mango::Matrix::Log(m);

			m.Log();

			for (unsigned row = 0; row < m.Rows(); row++)
			{
				for (unsigned col = 0; col < m.Cols(); col++)
				{
					for (unsigned page = 0; page < m.Pages(); page++)
					{
						Assert::AreEqual(m(row, col, page), m2(row, col, page), 0.0001f);
						Assert::AreEqual(m(row, col, page), log(float(row + col + page + 1)), 0.0001f);
					}
				}
			}


			m.Log();
		}


		TEST_METHOD(Matrix08_Reshape)
		{
			mango::Matrix m(3, 4, 2);

			float val = 0.0f;
			for (unsigned page = 0; page < m.Pages(); page++)
			{
				for (unsigned row = 0; row < m.Rows(); row++)
				{
					for (unsigned col = 0; col < m.Cols(); col++)
					{
						m(row, col, page) = val;
						val += 1;
					}
				}
			}

			m.Reshape(2, 4, 3);
			Assert::AreEqual(m.Rows(), 2u);
			Assert::AreEqual(m.Cols(), 4u);
			Assert::AreEqual(m.Pages(), 3u);
			for (unsigned page = 0; page < m.Pages(); page++)
			{
				for (unsigned row = 0; row < m.Rows(); row++)
				{
					for (unsigned col = 0; col < m.Cols(); col++)
					{
						Assert::AreEqual(m(row, col, page), float(page*m.Rows()*m.Cols() + row * m.Cols() + col), 0.0001f);
					}
				}
			}
		}

		TEST_METHOD(Matrix09_OperatorWithFloat)
		{
			mango::Matrix m1(3, 4, 2);
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						m1(row, col, page) = row + col + page;
					}
				}
			}

			mango::Matrix m2 = m1 + 4.5;
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m2(row, col, page), (row + col + page + 4.5f), 0.0001f);
					}
				}
			}

			m2 *= 1.7;
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m2(row, col, page), (row + col + page + 4.5f)*1.7f, 0.0001f);
					}
				}
			}

			mango::Matrix m4 = 2.0f - m1;
			mango::Matrix m5 = m1 - 2.0f;
			for (unsigned row = 0; row < 3; row++)
			{
				for (unsigned col = 0; col < 3; col++)
				{
					for (unsigned page = 0; page < 2; page++)
					{
						Assert::AreEqual(m4(row, col, page), -m5(row, col, page), 0.0001f);
					}
				}
			}

		}


		TEST_METHOD(Matrix10_Sum)
		{
			mango::Matrix m1(2, 3, 4);
			for (unsigned page = 0; page < m1.Pages(); page++)
			{
				for (unsigned row = 0; row < m1.Rows(); row++)
				{
					for (unsigned col = 0; col < m1.Cols(); col++)
					{
						m1(row, col, page) = 1;
					}
				}
			}
			mango::Matrix m2(m1);
			mango::Matrix m3(m1);

			m1.Sum(mango::Axis::Row);
			m2.Sum(mango::Axis::Col);
			m3.Sum(mango::Axis::Page);

			Assert::AreEqual(m1.Rows(), 1u);
			Assert::AreEqual(m1.Cols(), 3u);
			Assert::AreEqual(m1.Pages(), 4u);

			Assert::AreEqual(m2.Rows(), 2u);
			Assert::AreEqual(m2.Cols(), 1u);
			Assert::AreEqual(m2.Pages(), 4u);

			Assert::AreEqual(m3.Rows(), 2u);
			Assert::AreEqual(m3.Cols(), 3u);
			Assert::AreEqual(m3.Pages(), 1u);

			for (unsigned page = 0; page < 4; page++)
			{
				for (unsigned row = 0; row < 2; row++)
				{
					for (unsigned col = 0; col < 3; col++)
					{
						Assert::AreEqual(m1(0, col, page), 2.0f, 0.0001f);
						Assert::AreEqual(m2(row, 0, page), 3.0f, 0.0001f);
						Assert::AreEqual(m3(row, col, 0), 4.0f, 0.0001f);
					}
				}
			}

		}

		TEST_METHOD(Matrix11_Average)
		{
			mango::Matrix m1(2, 3, 4);
			for (unsigned page = 0; page < m1.Pages(); page++)
			{
				for (unsigned row = 0; row < m1.Rows(); row++)
				{
					for (unsigned col = 0; col < m1.Cols(); col++)
					{
						m1(row, col, page) = 1;
					}
				}
			}
			mango::Matrix m2(m1);
			mango::Matrix m3(m1);

			m1.Average(mango::Axis::Row);
			m2.Average(mango::Axis::Col);
			m3.Average(mango::Axis::Page);

			Assert::AreEqual(m1.Rows(), 1u);
			Assert::AreEqual(m1.Cols(), 3u);
			Assert::AreEqual(m1.Pages(), 4u);

			Assert::AreEqual(m2.Rows(), 2u);
			Assert::AreEqual(m2.Cols(), 1u);
			Assert::AreEqual(m2.Pages(), 4u);

			Assert::AreEqual(m3.Rows(), 2u);
			Assert::AreEqual(m3.Cols(), 3u);
			Assert::AreEqual(m3.Pages(), 1u);

			for (unsigned page = 0; page < 4; page++)
			{
				for (unsigned row = 0; row < 2; row++)
				{
					for (unsigned col = 0; col < 3; col++)
					{
						Assert::AreEqual(m1(0, col, page), 1.0f, 0.0001f);
						Assert::AreEqual(m2(row, 0, page), 1.0f, 0.0001f);
						Assert::AreEqual(m3(row, col, 0), 1.0f, 0.0001f);
					}
				}
			}
		}

	};
}