
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>

struct TablePrinter
{
    TablePrinter(const std::vector<int>& columnWidths) :
        m_columnWidths(columnWidths),
        m_columnCount(columnWidths.size())
    {
        calculate_total_table_width();
        create_row_separator();
        m_currentRowString.reserve(m_totalTableWidth);
    }

    void create_row_separator()
    {
        m_rowSeparator.reserve(m_totalTableWidth);

        m_rowSeparator.push_back('+');
        for (const auto& columnWidth : m_columnWidths)
        {
            for (unsigned i = 0; i < columnWidth+2; ++i)
            {
                m_rowSeparator.push_back('-');
            }
            m_rowSeparator.push_back('+');
        }
        m_rowSeparator.push_back('\n');
    }

    void add_spaces_to_current_row(unsigned count)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            m_currentRowString.push_back(' ');
        }
    }

    void calculate_total_table_width()
    {
        // For the separators
        m_totalTableWidth = (m_columnCount) * 3 + 1;
        for (const auto& columnWidth : m_columnWidths)
        {
            m_totalTableWidth += columnWidth;
        }
    }

    void start_color(const std::string& ansiColor)
    {
        m_currentRowString.append("\033[" + ansiColor + "m");
    }

    void end_color()
    {
        m_currentRowString.append("\033[0m");
    }

    void print_row(const std::vector<std::string>& stringRow, const std::string& ansiColor = "")
    {
        if (stringRow.size() != m_columnCount)
        {
            throw "sizes not equal";
        }

        std::vector<const char*> row;
        row.reserve(stringRow.size());
        for (const auto& column : stringRow)
        {
            row.push_back(column.c_str());
        }

        unsigned finishedColumnCount = 0;

        std::vector<unsigned> stringPositions(row.size(), 0);

        while (finishedColumnCount != m_columnCount)
        {
            m_currentRowString.append("| ");
            for (unsigned columnIndex = 0; columnIndex < row.size(); ++columnIndex)
            {   
                unsigned& stringPosition = stringPositions.at(columnIndex);
                const char* const& columnString = row.at(columnIndex);
                const int& columnWidth = m_columnWidths.at(columnIndex);

                if (columnString[stringPosition] == '\0')
                {
                    add_spaces_to_current_row(columnWidth);
                }
                else
                {
                    if (!ansiColor.empty())
                    {
                        start_color(ansiColor);
                    }

                    unsigned charIndex = 0;
                    while (true)
                    {
                        const char& columnChar = columnString[stringPosition];
                        if (columnChar == '\0')
                        {
                            add_spaces_to_current_row(columnWidth-charIndex);
                            ++finishedColumnCount;
                            break;
                        }
                        
                        ++stringPosition;

                        if (columnChar == '\n')
                        {
                            add_spaces_to_current_row(columnWidth-charIndex);
                            if (columnString[stringPosition] == '\0')
                            {
                                ++finishedColumnCount;
                            }
                            break;
                        }

                        // TODO: Swallow special characters like '\r' (I think???)
                        
                        m_currentRowString.push_back(columnChar);

                        if (columnWidth == ++charIndex)
                        {
                            if (columnString[stringPosition] == '\n')
                            {
                                ++stringPosition;
                            }

                            if (columnString[stringPosition] == '\0')
                            {
                                ++finishedColumnCount;
                            }
                            break;
                        }
                    }
                }

                if (!ansiColor.empty())
                {
                    end_color();
                }
                
                if (columnIndex+1 < row.size())
                {
                    m_currentRowString.append(" | ");
                }
            }
            m_currentRowString.append(" |\n");
        }
        std::cout << m_currentRowString;
        m_currentRowString.clear();
        std::cout << m_rowSeparator;
    }

    const std::vector<int> m_columnWidths;
    const unsigned m_columnCount;
    const char m_spaceChar = ' ';
    unsigned m_totalTableWidth = 0;
    std::string m_rowSeparator;
    std::string m_currentRowString;
};