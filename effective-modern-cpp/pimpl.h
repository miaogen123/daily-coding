#include<memory>

class Pimpl{
public:
	Pimpl();
	void out_str();
	Pimpl(Pimpl&& rhs);
	Pimpl(Pimpl& rhs);
	Pimpl& operator =(const Pimpl &rhs);
	Pimpl& operator =(Pimpl &&rhs);
	~Pimpl();
private:
	struct pimpl;
	std::unique_ptr<pimpl> P_im;
};

