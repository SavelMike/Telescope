#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<unsigned char> parse_stream(std::istream& in, const std::pair<size_t, size_t>& m_size)
{
	size_t v_size = m_size.first * m_size.second;
	std::vector<unsigned char> m_vector;
	unsigned char c;
	
	for (int i = 0; i < v_size; i++) {
		in>>c;
		if (in.eof()) {
			// Input stream had not enough elements. It is inconsistent number of elements
			throw std::invalid_argument("End of input stream."); // Programm aborts here
			// Q: does input stream have to contain exatly v_size characters to be consistent.
			// For now I assume no.
		}
		m_vector.push_back(c);
	}
	
	return m_vector;
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec)
{
	std::vector<unsigned char> tmp_vec;

	// First row of result
	for (int i = 0; i < m_size.second; i++) {
		tmp_vec.push_back(vec.at(m_size.second * (m_size.first - 1) + i));
	}

	for (int i = 0; i < m_size.second * (m_size.first - 1); i++) {
		tmp_vec.push_back(vec.at(i));
	}

	vec = tmp_vec;
}

void print_vector(const std::pair<size_t, size_t>& m_size, const std::vector<unsigned char>& vec)
{
	for (int i = 0; i < m_size.first; i++) {
		for (int j = 0; j < m_size.second; j++) {
			std::cout << "'"  << vec.at(i * m_size.second + j) << "' ";
		}
		std::cout << "\n";
	}
}

int main(void)
{
	std::pair<size_t, size_t> in_size(4, 4);
	std::vector<unsigned char> tmp = parse_stream(std::cin, in_size);

	print_vector(in_size, tmp);

	rotate_down(in_size, tmp);
	std::cout << "Resulting matrix:\n";
	print_vector(in_size, tmp);
	
	return 0;
}
