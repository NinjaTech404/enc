class BorderFormatter {
private:
    static std::vector<std::string> wrap_text(const std::string& text, int width) {
        std::vector<std::string> lines;
        std::istringstream iss(text);
        std::string word;
        std::string current_line;
        
        while (iss >> word) {
            if (current_line.length() + word.length() + (current_line.empty() ? 0 : 1) > width) {
                if (!current_line.empty()) {
                    lines.push_back(current_line);
                    current_line = word;
                } else {
                    // Word is longer than width, split it
                    while (word.length() > width) {
                        lines.push_back(word.substr(0, width));
                        word = word.substr(width);
                    }
                    current_line = word;
                }
            } else {
                if (!current_line.empty()) {
                    current_line += " ";
                }
                current_line += word;
            }
        }
        
        if (!current_line.empty()) {
            lines.push_back(current_line);
        }
        
        return lines;
    }
    
    static std::string create_border_with_text(int width, char border_char, 
                                              const std::string& center_text = "") {
        if (center_text.empty()) {
            return std::string(width, border_char);
        }
        
        int border_length = width - center_text.length() - 2; // -2 for spaces
        if (border_length < 2) {
            // Not enough space for borders, just use text
            return center_text.substr(0, width);
        }
        
        int left_border = border_length / 2;
        int right_border = border_length - left_border;
        
        return std::string(left_border, border_char) + " " + 
               center_text + " " + 
               std::string(right_border, border_char);
    }

public:
    // Version 1: With fixed "OUTPUT STARTS"/"OUTPUT ENDS"
    static std::string format_with_labels(const std::string& content, 
                                         int width = 60, 
                                         char border_char = '=') {
        // Create borders with labels
        std::string top_border = create_border_with_text(width, border_char, "OUTPUT STARTS");
        std::string bottom_border = create_border_with_text(width, border_char, "OUTPUT ENDS");
        
        // Wrap content
        auto lines = wrap_text(content, width);
        
        // Build output
        std::string result = top_border + "\n";
        for (const auto& line : lines) {
            result += line + "\n";
        }
        result += bottom_border;
        
        return result;
    }
    
    // Version 2: Customizable header/footer text
    static std::string format(const std::string& content, 
                             int width = 60, 
                             char border_char = '=',
                             const std::string& header_text = "",
                             const std::string& footer_text = "") {
        // Create borders
        std::string top_border = create_border_with_text(width, border_char, header_text);
        std::string bottom_border = create_border_with_text(width, border_char, footer_text);
        
        // Wrap content
        auto lines = wrap_text(content, width);
        
        // Build output
        std::string result = top_border + "\n";
        for (const auto& line : lines) {
            result += line + "\n";
        }
        result += bottom_border;
        
        return result;
    }
    
    // Version 3: Box style with header/footer
    static std::string format_box(const std::string& content,
                                 int width = 60,
                                 char horizontal = '=',
                                 char vertical = '|',
                                 const std::string& header_text = "",
                                 const std::string& footer_text = "") {
        // Create top border with optional header
        std::string top_border;
        if (header_text.empty()) {
            top_border = std::string(width, horizontal);
        } else {
            top_border = create_border_with_text(width, horizontal, header_text);
        }
        
        // Create bottom border with optional footer
        std::string bottom_border;
        if (footer_text.empty()) {
            bottom_border = std::string(width, horizontal);
        } else {
            bottom_border = create_border_with_text(width, horizontal, footer_text);
        }
        
        // Wrap content
        auto lines = wrap_text(content, width - 4); // Account for side borders
        
        // Build box
        std::string result = top_border + "\n";
        for (const auto& line : lines) {
            // Calculate padding for full width
            int total_padding = width - 2 - line.length(); // -2 for side borders
            int left_padding = total_padding / 2;
            int right_padding = total_padding - left_padding;
            
            result += vertical + 
                     std::string(left_padding, ' ') + 
                     line + 
                     std::string(right_padding, ' ') + 
                     vertical + "\n";
        }
        result += bottom_border;
        
        return result;
    }
    
    // Version 4: Convenience methods for common patterns
    static std::string format_section(const std::string& content,
                                     const std::string& section_name,
                                     int width = 60,
                                     char border_char = '=') {
        return format(content, width, border_char, 
                     "SECTION: " + section_name, 
                     "END " + section_name);
    }
    
    static std::string format_key_output(const std::string& key_data,
                                        const std::string& key_type = "KEY",
                                        int width = 64,
                                        char border_char = '-') {
        return format(key_data, width, border_char,
                     "BEGIN " + key_type,
                     "END " + key_type);
    }
};
