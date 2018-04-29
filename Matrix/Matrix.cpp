#include "stdafx.h"
#include "Matrix.h"



mango::Matrix::Matrix(unsigned rows, unsigned cols, unsigned pages)
{
	if (rows <= 0 || cols <= 0 || pages <= 0)
	{
		throw std::length_error("Invalid matrix dimension");
	}

	rows_ = rows;
	cols_ = cols;
	pages_ = pages;

	data_ = new float[rows_*cols_*pages_]();
}

mango::Matrix::Matrix(const Matrix & m)
{
	rows_ = m.rows_;
	cols_ = m.cols_;
	pages_ = m.pages_;

	if (m.data_ != nullptr)
	{
		data_ = new float[rows_*cols_*pages_];

		for (unsigned i = 0; i < rows_*cols_*pages_; i++)
			data_[i] = m.data_[i];
	}


}

mango::Matrix::Matrix(Matrix && m)
{
	rows_ = m.Rows();
	cols_ = m.Cols();
	pages_ = m.Pages();

	data_ = m.data_;

	m.rows_ = 0;
	m.cols_ = 0;
	m.pages_ = 0;
	m.data_ = nullptr;
}

mango::Matrix::~Matrix()
{
	delete[] data_;
}

mango::Matrix& mango::Matrix::operator=(const Matrix& m)
{
	if (this == &m)
	{
		return *this;
	}

	rows_ = m.Rows();
	cols_ = m.Cols();
	pages_ = m.Pages();

	delete[] data_;
	if (m.data_ == nullptr)
	{
		data_ = nullptr;
	}
	else
	{
		data_ = new float[rows_*cols_*pages_];

		for (unsigned i = 0; i < rows_*cols_*pages_; i++)
			data_[i] = m.data_[i];
	}

	return *this;
}

mango::Matrix& mango::Matrix::operator=(Matrix && m)
{
	rows_ = m.Rows();
	cols_ = m.Cols();
	pages_ = m.Pages();

	delete[] data_;
	data_ = m.data_;

	m.data_ = nullptr;
	m.rows_ = 0;
	m.cols_ = 0;
	m.pages_ = 0;

	return *this;
}

mango::Matrix& mango::Matrix::operator+=(const float val)
{
	for (unsigned i = 0; i < rows_*cols_*pages_; i++)
		data_[i] += val;

	return *this;
}

mango::Matrix& mango::Matrix::operator-=(const float val)
{
	for (unsigned i = 0; i < rows_*cols_*pages_; i++)
		data_[i] -= val;

	return *this;
}

mango::Matrix& mango::Matrix::operator*=(const float val)
{
	for (unsigned i = 0; i < rows_*cols_*pages_; i++)
		data_[i] *= val;

	return *this;
}

mango::Matrix& mango::Matrix::operator/=(const float val)
{
	for (unsigned i = 0; i < rows_*cols_*pages_; i++)
		data_[i] /= val;

	return *this;
}

mango::Matrix& mango::Matrix::Reshape(unsigned rows, unsigned cols, unsigned pages)
{
	if (rows*cols*pages != rows_ * cols_*pages_)
	{
		throw std::length_error("Invalid matrix size");
	}
	rows_ = rows;
	cols_ = cols;
	pages_ = pages;
	return *this;
}

mango::Matrix& mango::Matrix::Sum(Axis axis)
{
	unsigned end;
	switch (axis)
	{
	case mango::Axis::Row:
		end = rows_;
		break;
	case mango::Axis::Col:
		end = cols_;
		break;
	case mango::Axis::Page:
		end = pages_;
		break;
	}

	return Sum(axis, 0, end);
}

mango::Matrix& mango::Matrix::Sum(Axis axis, unsigned start, unsigned end)
{
	if (end <= start)
	{
		throw std::invalid_argument("Invalid axis range");
	}

	// TODO: insert return statement here
	if (axis == mango::Axis::Row)
	{
		if (end > rows_)
			throw std::invalid_argument("Invalid axis range");

		float* data_new = new float[cols_*pages_]();

		for (unsigned page = 0; page < pages_; page++)
			for (unsigned row = start; row < end; row++)
				for (unsigned col = 0; col < cols_; col++)
					data_new[page*cols_ + col] += this->operator()(row, col, page);

		rows_ = 1u;
		delete[] data_;
		data_ = data_new;
		return *this;
	}
	else if (axis == mango::Axis::Col)
	{
		if (end > cols_)
			throw std::invalid_argument("Invalid axis range");

		float* data_new = new float[rows_*pages_]();

		for (unsigned page = 0; page < pages_; page++)
			for (unsigned row = 0; row < rows_; row++)
				for (unsigned col = start; col < end; col++)
					data_new[page*rows_ + row] += this->operator()(row, col, page);

		cols_ = 1u;
		delete[] data_;
		data_ = data_new;
		return *this;
	}
	else if (axis == mango::Axis::Page)
	{
		if (end > pages_)
			throw std::invalid_argument("Invalid axis range");

		float* data_new = new float[rows_*cols_]();
		for (unsigned page = start; page < end; page++)
			for (unsigned row = 0; row < rows_; row++)
				for (unsigned col = 0; col < cols_; col++)
					data_new[row*cols_ + col] += this->operator()(row, col, page);

		pages_ = 1u;
		delete[] data_;
		data_ = data_new;
		return *this;
	}
	else
	{
		throw std::invalid_argument("Invalid input argument");
	}
}

mango::Matrix& mango::Matrix::Average(mango::Axis axis)
{
	unsigned length;
	switch (axis)
	{
	case mango::Axis::Row:
		length = rows_;
		break;
	case mango::Axis::Col:
		length = cols_;
		break;
	case mango::Axis::Page:
		length = pages_;
		break;
	}

	Sum(axis);
	(*this) /= float(length);

	return *this;
}

mango::Matrix& mango::Matrix::Average(Axis axis, unsigned start, unsigned end)
{
	Sum(axis, start, end);
	(*this) /= float(end - start);
	return *this;
}

mango::Matrix& mango::Matrix::AllNoLessThan(float threshold)
{
	for (unsigned idx = 0; idx < rows_*cols_*pages_; idx++)
	{
		if (data_[idx] < threshold)
			data_[idx] = threshold;
	}
	return *this;
}

mango::Matrix& mango::Matrix::Log()
{
	for (unsigned idx = 0; idx < rows_*cols_*pages_; idx++)
		data_[idx] = log(data_[idx]);
	return *this;
}

mango::Matrix mango::Matrix::Log(const Matrix & m)
{
	Matrix m_new = m;
	return std::move(m_new.Log());
}

mango::Matrix mango::Matrix::Sum(const Matrix & m, Axis axis)
{
	unsigned end;	// start is always 0
	switch (axis)
	{
	case mango::Axis::Row:
		end = m.Rows();
		break;
	case mango::Axis::Col:
		end = m.Cols();
		break;
	case mango::Axis::Page:
		end = m.Pages();
		break;
	}

	return Sum(m, axis, 0, end);
}

mango::Matrix mango::Matrix::Sum(const Matrix & m, Axis axis, unsigned start, unsigned end)
{
	if (end<=start)
	{
		throw std::invalid_argument("Invalid range");
	}

	unsigned rows = m.Rows();
	unsigned cols = m.Cols();
	unsigned pages = m.Pages();

	unsigned zero = 0;
	unsigned row, col, page;	// index for Matrix m
	unsigned *prow = &row;		// index for result matrix
	unsigned *pcol = &col;		// index for result matrix
	unsigned *ppage = &page;	// index for result matrix

	unsigned row_start = 0, row_end = rows;
	unsigned col_start = 0, col_end = cols;
	unsigned page_start = 0, page_end = pages;

	switch (axis)
	{
	case mango::Axis::Row:
		rows = 1;
		prow = &zero;
		row_start = start;
		row_end = end;
		break;
	case mango::Axis::Col:
		cols = 1;
		pcol = &zero;
		col_start = start;
		col_end = end;
		break;
	case mango::Axis::Page:
		pages = 1;
		ppage = &zero;
		page_start = start;
		page_end = end;
		break;
	}

	Matrix m_new(rows, cols, pages);

	for (page = page_start; page < page_end; page++)
		for (row = row_start; row < row_end; row++)
			for (col = col_start; col < col_end; col++)
				m_new(*prow, *pcol, *ppage) += m(row, col, page);

	return m_new;
}

mango::Matrix mango::Matrix::Average(const Matrix & m, Axis axis)
{
	Matrix m_new = Sum(m, axis);

	switch (axis)
	{
	case mango::Axis::Row:
		m_new /= float(m.Rows());
		break;
	case mango::Axis::Col:
		m_new /= float(m.Cols());
		break;
	case mango::Axis::Page:
		m_new /= float(m.Pages());
		break;
	}

	return m_new;
}

mango::Matrix mango::Matrix::Average(const Matrix & m, Axis axis, unsigned start, unsigned end)
{
	Matrix m_new = Sum(m, axis, start, end);
	m_new /= float(end - start);
	return m_new;
}

mango::Matrix mango::operator+(const Matrix & m1, const Matrix & m2)
{
	if (m1.Rows() == m2.Rows() && m1.Cols() == m2.Cols() && m1.Pages() == m2.Pages())
	{
		Matrix m_new(m1.Rows(), m1.Cols(), m1.Pages());
		for (unsigned page = 0; page < m1.Pages(); page++)
			for (unsigned row = 0; row < m1.Rows(); row++)
				for (unsigned col = 0; col < m1.Cols(); col++)
					m_new(row, col, page) = m1(row, col, page) + m2(row, col, page);
		return m_new;
	}
	// Broadcasting
	unsigned row, col, page;				// index in the for loop
	unsigned rows, cols, pages;				// size of the result matrix
	unsigned *prow, *pcol, *ppage;			// index for this matrix
	unsigned *prow_m, *pcol_m, *ppage_m;	// index for matrix m
	unsigned zero = 0;

	// judgement for row
	if (m1.Rows() == m2.Rows())
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &row;
	}
	else if (m1.Rows() == 1)
	{
		rows = m2.Rows();
		prow = &zero;
		prow_m = &row;
	}
	else if (m2.Rows() == 1)
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for col
	if (m1.Cols() == m2.Cols())
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &col;
	}
	else if (m1.Cols() == 1)
	{
		cols = m2.Cols();
		pcol = &zero;
		pcol_m = &col;
	}
	else if (m2.Cols() == 1)
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for page
	if (m1.Pages() == m2.Pages())
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &page;
	}
	else if (m1.Pages() == 1)
	{
		pages = m2.Pages();
		ppage = &zero;
		ppage_m = &page;
	}
	else if (m2.Pages() == 1)
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	Matrix m_new(rows, cols, pages);
	for (page = 0; page < pages; page++)
		for (row = 0; row < rows; row++)
			for (col = 0; col < cols; col++)
				m_new(row, col, page) = m1(*prow, *pcol, *ppage) + m2(*prow_m, *pcol_m, *ppage_m);

	return m_new;
}

mango::Matrix mango::operator-(const Matrix & m1, const Matrix & m2)
{
	if (m1.Rows() == m2.Rows() && m1.Cols() == m2.Cols() && m1.Pages() == m2.Pages())
	{
		Matrix m_new(m1.Rows(), m1.Cols(), m1.Pages());
		for (unsigned page = 0; page < m1.Pages(); page++)
			for (unsigned row = 0; row < m1.Rows(); row++)
				for (unsigned col = 0; col < m1.Cols(); col++)
					m_new(row, col, page) = m1(row, col, page) - m2(row, col, page);
		return m_new;
	}
	// Broadcasting
	unsigned row, col, page;				// index in the for loop
	unsigned rows, cols, pages;				// size of the result matrix
	unsigned *prow, *pcol, *ppage;			// index for this matrix
	unsigned *prow_m, *pcol_m, *ppage_m;	// index for matrix m
	unsigned zero = 0;

	// judgement for row
	if (m1.Rows() == m2.Rows())
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &row;
	}
	else if (m1.Rows() == 1)
	{
		rows = m2.Rows();
		prow = &zero;
		prow_m = &row;
	}
	else if (m2.Rows() == 1)
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for col
	if (m1.Cols() == m2.Cols())
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &col;
	}
	else if (m1.Cols() == 1)
	{
		cols = m2.Cols();
		pcol = &zero;
		pcol_m = &col;
	}
	else if (m2.Cols() == 1)
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for page
	if (m1.Pages() == m2.Pages())
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &page;
	}
	else if (m1.Pages() == 1)
	{
		pages = m2.Pages();
		ppage = &zero;
		ppage_m = &page;
	}
	else if (m2.Pages() == 1)
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	Matrix m_new(rows, cols, pages);
	for (page = 0; page < pages; page++)
		for (row = 0; row < rows; row++)
			for (col = 0; col < cols; col++)
				m_new(row, col, page) = m1(*prow, *pcol, *ppage) - m2(*prow_m, *pcol_m, *ppage_m);

	return m_new;
}

mango::Matrix mango::operator*(const Matrix & m1, const Matrix & m2)
{
	if (m1.Rows() == m2.Rows() && m1.Cols() == m2.Cols() && m1.Pages() == m2.Pages())
	{
		Matrix m_new(m1.Rows(), m1.Cols(), m1.Pages());
		for (unsigned page = 0; page < m1.Pages(); page++)
			for (unsigned row = 0; row < m1.Rows(); row++)
				for (unsigned col = 0; col < m1.Cols(); col++)
					m_new(row, col, page) = m1(row, col, page) * m2(row, col, page);
		return m_new;
	}
	// Broadcasting
	unsigned row, col, page;				// index in the for loop
	unsigned rows, cols, pages;				// size of the result matrix
	unsigned *prow, *pcol, *ppage;			// index for this matrix
	unsigned *prow_m, *pcol_m, *ppage_m;	// index for matrix m
	unsigned zero = 0;

	// judgement for row
	if (m1.Rows() == m2.Rows())
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &row;
	}
	else if (m1.Rows() == 1)
	{
		rows = m2.Rows();
		prow = &zero;
		prow_m = &row;
	}
	else if (m2.Rows() == 1)
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for col
	if (m1.Cols() == m2.Cols())
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &col;
	}
	else if (m1.Cols() == 1)
	{
		cols = m2.Cols();
		pcol = &zero;
		pcol_m = &col;
	}
	else if (m2.Cols() == 1)
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for page
	if (m1.Pages() == m2.Pages())
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &page;
	}
	else if (m1.Pages() == 1)
	{
		pages = m2.Pages();
		ppage = &zero;
		ppage_m = &page;
	}
	else if (m2.Pages() == 1)
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	Matrix m_new(rows, cols, pages);
	for (page = 0; page < pages; page++)
		for (row = 0; row < rows; row++)
			for (col = 0; col < cols; col++)
				m_new(row, col, page) = m1(*prow, *pcol, *ppage) * m2(*prow_m, *pcol_m, *ppage_m);

	return m_new;
}

mango::Matrix mango::operator/(const Matrix & m1, const Matrix & m2)
{
	if (m1.Rows() == m2.Rows() && m1.Cols() == m2.Cols() && m1.Pages() == m2.Pages())
	{
		Matrix m_new(m1.Rows(), m1.Cols(), m1.Pages());
		for (unsigned page = 0; page < m1.Pages(); page++)
			for (unsigned row = 0; row < m1.Rows(); row++)
				for (unsigned col = 0; col < m1.Cols(); col++)
					m_new(row, col, page) = m1(row, col, page) / m2(row, col, page);
		return m_new;
	}
	// Broadcasting
	unsigned row, col, page;				// index in the for loop
	unsigned rows, cols, pages;				// size of the result matrix
	unsigned *prow, *pcol, *ppage;			// index for this matrix
	unsigned *prow_m, *pcol_m, *ppage_m;	// index for matrix m
	unsigned zero = 0;

	// judgement for row
	if (m1.Rows() == m2.Rows())
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &row;
	}
	else if (m1.Rows() == 1)
	{
		rows = m2.Rows();
		prow = &zero;
		prow_m = &row;
	}
	else if (m2.Rows() == 1)
	{
		rows = m1.Rows();
		prow = &row;
		prow_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for col
	if (m1.Cols() == m2.Cols())
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &col;
	}
	else if (m1.Cols() == 1)
	{
		cols = m2.Cols();
		pcol = &zero;
		pcol_m = &col;
	}
	else if (m2.Cols() == 1)
	{
		cols = m1.Cols();
		pcol = &col;
		pcol_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	// judgement for page
	if (m1.Pages() == m2.Pages())
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &page;
	}
	else if (m1.Pages() == 1)
	{
		pages = m2.Pages();
		ppage = &zero;
		ppage_m = &page;
	}
	else if (m2.Pages() == 1)
	{
		pages = m1.Pages();
		ppage = &page;
		ppage_m = &zero;
	}
	else
	{
		throw std::length_error("Two matrix size do not match");
	}

	Matrix m_new(rows, cols, pages);
	for (page = 0; page < pages; page++)
		for (row = 0; row < rows; row++)
			for (col = 0; col < cols; col++)
				m_new(row, col, page) = m1(*prow, *pcol, *ppage) / m2(*prow_m, *pcol_m, *ppage_m);

	return m_new;
}

mango::Matrix mango::operator+(const Matrix & m, const float & val)
{
	mango::Matrix m_new(m);
	m_new += val;
	return m_new;
}

mango::Matrix mango::operator-(const Matrix & m, const float & val)
{
	mango::Matrix m_new(m);
	m_new -= val;
	return m_new;
}

mango::Matrix mango::operator*(const Matrix & m, const float & val)
{
	mango::Matrix m_new(m);
	m_new *= val;
	return m_new;
}

mango::Matrix mango::operator/(const Matrix & m, const float & val)
{
	mango::Matrix m_new(m);
	m_new /= val;
	return m_new;
}

mango::Matrix mango::operator+(const float & val, const Matrix & m)
{
	return m + val;
}

mango::Matrix mango::operator-(const float & val, const Matrix & m)
{
	mango::Matrix m_new(m.Rows(), m.Cols(), m.Pages());

	for (unsigned page = 0; page < m.Pages(); page++)
		for (unsigned row = 0; row < m.Rows(); row++)
			for (unsigned col = 0; col < m.Cols(); col++)
				m_new(row, col, page) = val - m(row, col, page);

	return m_new;
}

mango::Matrix mango::operator*(const float & val, const Matrix & m)
{
	return m * val;
}

mango::Matrix mango::operator/(const float & val, const Matrix & m)
{
	mango::Matrix m_new(m.Rows(), m.Cols(), m.Pages());

	for (unsigned page = 0; page < m.Pages(); page++)
		for (unsigned row = 0; row < m.Rows(); row++)
			for (unsigned col = 0; col < m.Cols(); col++)
				m_new(row, col, page) = val / m(row, col, page);

	return m_new;
}
