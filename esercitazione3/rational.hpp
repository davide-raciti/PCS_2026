#pragma once // dice al compilatore di includere il file una volta sola
#include <concepts>

// definizione della classe dei razionali
template<typename I> requires std::integral<I>
class rational
{
    I num_;
    I den_;

    // metodo di Euclide tra due interi, chiamata in semplifica()
    I calcolaMCD(I a, I b) {
        I resto;
        while (b != 0) {
            resto = a % b;
            a = b;
            b = resto;
        }
        return a;
    }

    public:
        // costruttore di default (se definisci senza passare argomenti)
        rational(){
            num_ =0; den_ =1;
        }
        
        // costruttore user-defined (se definisci passando argomenti)
        rational(const I& pnum, const I& pden){
            // gestione eccezioni
            if (pden == 0) {
                if (pnum == 0) {
                    num_ = 0; den_ = 0; // costruisce un NaN
                }
                else {
                    num_ = 1; den_ = 0; // costruisce un Inf
                }
            }
            else {
                num_ = pnum;
                den_ = pden;
                semplifica();
            }
        }
        
        // metodi getter che permettono di chiedere i valori privati num_ e den_
        I num() const {return num_;};
        I den() const {return den_;};
        
        // (+=)
        rational& operator+=(const rational& other) {
            // a += NaN -> NaN
                // siccome ho messo prima la condizione su NaN, gestisce anche 
                // il caso Inf += NaN -> NaN
            if((num_== 0 && den_ ==0) || (other.num_== 0 && other.den_ ==0))
            {
                num_ = 0; den_= 0;
            }
            // a += Inf -> Inf
            else if((num_ != 0 && den_ ==0) || (other.num_ !=0 && other.den_ ==0))
            {
                num_ =1; den_ =0;
            }
            // addendi ben definiti
            else
            {
                num_ = (num_ *other.den_) + (other.num_ *den_);
                den_ = other.den_ * den_;
            }
            semplifica();           
            return *this;
        }
        
        // (+) definito tramite (+=)
        rational operator+(const rational& other) const {
            rational ret=*this;
            ret += other;
            return ret;
        }
        
        // (-=) 
        rational& operator-=(const rational& other) {
            // a -= NaN -> NaN
                // siccome ho messo prima la condizione su NaN, gestisce anche 
                // il caso Inf -= NaN -> NaN
            if((num_ == 0 && den_ ==0) || (other.num_ ==0 && other.den_ ==0)) {
                num_ =0; den_ =0;
            }
            // Inf -= Inf -> NaN
            else if((num_ != 0 && den_ ==0) && (other.num_ !=0 && other.den_ ==0)) {
                num_ =0; den_ =0;
            }
            // a -= Inf -> Inf
            else if(den_ == 0 || other.den_ == 0) {
                num_ = 1; den_ = 0;
            }
            // addendi ben definiti
            else {
            num_ = (num_ *other.den_)-(other.num_ *den_);
            den_ = other.den_ *den_;
            }
        semplifica();
        return *this;
        }

        // (-) definito tramite (-=)
        rational operator-(const rational& other) const {
            rational ret=*this;
            ret -= other;
            return ret;
        }

        // (*=)
        rational& operator*=(const rational& other) {
            // a *= NaN -> NaN
            if ((num_==0 && den_==0) || (other.num_==0 && other.den_==0)){
                num_ = 0; den_ = 0;
            }
            // 0 *= Inf -> NaN
            else if ((num_==0 && other.den_==0) || (den_==0 && other.num_==0)){
                num_ = 0; den_ = 0;
            }
            // a!=0 *= Inf -> Inf
            else if ((den_ == 0 || other.den_ == 0)){
                num_ = 1; den_ = 0;
            }
            // fattori ben definiti
            else{
            num_ = num_ *other.num_;
            den_ = den_ *other.den_;
            }
            semplifica();
            return *this;
        }

        // (*)
        rational operator*(const rational& other) const {
            rational ret=*this;
            ret *= other;
            return ret;
        }
        
        // (/=)
        rational& operator/=(const rational& other) {
            // almeno un fattore NaN -> NaN
            if ((num_ == 0 && den_ == 0) || (other.num_ == 0 && other.den_ == 0)) {
                num_ = 0; den_ = 0;
            }
            // forme indeterminate 0/0 e Inf/Inf -> NaN
            else if ((num_ == 0 && other.num_ == 0) || (den_ == 0 && other.den_ == 0)) {
                num_ = 0; den_ = 0;
            }
            // a /= 0 oppure Inf /= a -> Inf
            else if (other.num_ == 0 || den_ == 0) {
                num_ = 1; den_ = 0;
            }
            // fattori ben definiti (gestisce anche a / Inf che fa 0 per la gestione in *=)
            else{
                num_ = num_ *other.den_;
                den_ = den_ *other.num_;
            }
            semplifica();
            return *this;
        }
        
        // (/) 
        rational operator/(const rational& other) const {
            rational ret=*this;
            ret /= other;
            return ret;
        }


        void semplifica(){
            if (den_ == 0) return; // per evitare calcoli se Inf o NaN

            // calcolo MCD usando i valori assoluti e aggiorno num_ e den_
            I gcd = calcolaMCD(std::abs(num_), std::abs(den_));
            num_ /= gcd;
            den_ /= gcd;

            // standardizzazione del segno, sposto il segno - sempre al numeratore
            // 1 / (-2) -> -1 / 2
            if (den_ < 0) {
                num_ = -num_;
                den_ = -den_;
            }
        }
};

// definizione dell'operatore di stampa
template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r) 
    // prende in input:
    // os: lo stream di output 
    // r: oggetto rational passato per const reference
{   
    // se den nullo
    if(r.den()==0) {
        // se anche num nullo -> NaN
        if(r.num()==0) {
            os << "Nan";
        }
        // altrimenti (se num non nullo) -> Inf
        else {
            os << "Inf";
        }
    }
    // altrimenti se den non nullo e num nullo
    else if (r.num() == 0 && r.den() != 0) {
        os << 0;
    }
    // altrimenti (se den non nullo)
    else {
        os << r.num()<< "/" <<r.den(); // mantieni il segno
    }
return os;
}
