// C++ in 199 Pages - 8.8 Smart pointers: unique_ptr and shared_ptr
// Build: g++ -std=c++17 08_smart_pointers.cpp -o smart && ./smart

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Document {
public:
    explicit Document(const std::string& title) : title_(title) {
        std::cout << "  open \"" << title_ << "\"\n";
    }
    ~Document() { std::cout << "  close \"" << title_ << "\"\n"; }
    const std::string& title() const { return title_; }
private:
    std::string title_;
};

int main() {
    std::cout << "unique_ptr: exactly one owner\n";
    {
        std::unique_ptr<Document> draft = std::make_unique<Document>("Draft.docx");
        std::cout << "  editing " << draft->title() << "\n";
        std::unique_ptr<Document> moved = std::move(draft);   // ownership is handed over
        std::cout << "  draft is now " << (draft ? "set" : "empty") << "\n";
    }   // 'moved' goes out of scope: the document is deleted automatically

    std::cout << "shared_ptr: many owners, deleted when the last one lets go\n";
    std::shared_ptr<Document> report = std::make_shared<Document>("Report.pdf");
    {
        std::vector<std::shared_ptr<Document>> openTabs = {report, report};
        std::cout << "  owners while tabs are open: " << report.use_count() << "\n";
    }
    std::cout << "  owners after tabs close: " << report.use_count() << "\n";
    report.reset();                                           // last owner lets go
    std::cout << "Done. No 'delete' was written anywhere.\n";
    return 0;
}
