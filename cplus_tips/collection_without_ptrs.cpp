/**
 * From Sean Parent's talk on C++ Seasoning
 * A container oblivious to shared_ptr headache
 * g++ -std=c++14
 */
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;

class object_t {
	public:
	template <typename T>
	object_t(T x) : self_(std::make_shared<model<T>>(std::move(x))) {}

	void draw(ostream& out, size_t position) const
	{
		self_->draw_(out, position); 
	}

	private:
	struct concept_t {
		virtual ~concept_t() = default;
		virtual void draw_(ostream&, size_t) const = 0;
	};

	template <typename T>
	struct model : concept_t {
		model(T x) : data_(std::move(x)) {}
		void draw_(ostream& out, size_t position) const
		{
			data_.draw(out, position); 
		}

		T data_;
	};

	std::shared_ptr<const concept_t> self_;

};

class my_class_t 
{
	public:
	void draw(ostream& out, size_t position) const
	{
		out << string(position, ' ') << "myclass_t" << std::endl;
	}
};

using document_t = std::vector<object_t>;

void draw(const document_t& doc, ostream& out, size_t position) {
	out << string(position, ' ') << "<doc>" << std::endl;
	for (const auto& e : doc) e.draw(out, position + 2);
	out << string(position, ' ') << "</doc>" << std::endl;
}

int main()
{
	document_t document;

	document.emplace_back(my_class_t());

	draw(document, std::cout, 0);
}
