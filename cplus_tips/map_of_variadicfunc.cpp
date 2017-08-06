#include <map>
#include <typeinfo>
#include <typeindex>

template <typename ReturnType>
class VariadicFuncMap
{
        typedef std::map<std::type_index, ReturnType(*)()> FuncMap;
		FuncMap m_funcs;
public:
 
		/**
		 * register func
		 */
        template <typename ...A1>
        VariadicFuncMap<ReturnType> add (ReturnType(*f)(A1...))
        {
                m_funcs[typeid(ReturnType(A1...))] = (ReturnType(*)()) f;
                return *this;
        }
 
		/**
		 * execute func
		 */
        template <typename ...A1>
        ReturnType operator()(A1... a1) const
        {
                typename FuncMap::const_iterator it = m_funcs.find(typeid(ReturnType(A1...)));

                if (it != m_funcs.end())
                {
                        ReturnType(*f)(A1...) = (ReturnType(*)(A1...))(it->second);
                        (*f)(a1...);
                }
        }
};

struct Node {
};


Node AddInt(int a);
Node AddChar2(char a, char b);

int main()
{
	VariadicFuncMap<Node> a;
	a.add(AddInt);
	a.add(AddChar2);
}

