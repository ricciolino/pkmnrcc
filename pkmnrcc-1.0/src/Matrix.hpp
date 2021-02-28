#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

template <typename T>
class Matrix {

    private:
        T** data;
        unsigned int N; // rows
        unsigned int M; // columns

    public:

        void Clear() {
            if (data != nullptr) {
                for (unsigned int i = 0; i < N; i++) {
                    if (data[i] != nullptr) {
                        delete[] data[i]; // delete all columns of row i-th
                    }
                }
                delete[] data;
            }
            data = nullptr;
            N = 0;
            M = 0;
        };

        bool Init(const unsigned int N_, const unsigned int M_) {
            this->Clear();
            if (N_ <= 0 || M_ <= 0) {
                std::cerr << "Can not generate matrix " << N_ << "x" << M_ << std::endl;
                return false;
            }
            if (N_ > 0 && M_ > 0) {
                N = N_;
                M = M_;
                data = new T*[N];
                for (unsigned int i = 0; i < N; i++) {
                    data[i] = new T[M];
                }
            }
            return true;
        }

        Matrix(const unsigned int N_, const unsigned int M_):N(0),M(0),data(nullptr) {
            this->Init(N_, M_);
        };
        
        Matrix():N(0),M(0),data(nullptr) {
        };

        ~Matrix() {
            this->Clear();
        };

        Matrix(const Matrix& m):N(0),M(0),data(nullptr) {
            this->Init(m.N, m.M);
            for (unsigned int i = 0; i < N; i++) {
                for (unsigned int j = 0; j < M; j++) {
                    data[i][j] = m.Get(i, j);;
                }
            }
        }

        Matrix& operator=(const Matrix& m) {
            if (this != &m) {
                this->Init(m.N, m.M);
                for (unsigned int i = 0; i < N; i++) {
                    for (unsigned int j = 0; j < M; j++) {
                        data[i][j] = m.Get(i,j);
                    }
                }
            }
            return *this;
        }

        void SetAllAtX(const T& x) {
            for (unsigned int i = 0; i < N; i++) {
                for (unsigned int j = 0; j < M; j++) {
                    data[i][j] = x;
                }
            }
        }

        void Print(bool verbose = false) const {
            if (N != 0 && M != 0 && data != nullptr) {
                if (verbose) { std::cout<<"column"; for (unsigned int k = 0; k < M; ++k) if (k < 10) std::cout << "[0" << k << "]"; else std::cout << "[" << k << "]"; std::cout << std::endl; }
                for (unsigned int i = 0; i < N; i++) {
                    if (verbose) { if (i < 10) std::cout<<"row[0" << i << "]"<<" "; else std::cout<<"row[" << i << "]"<<" "; }
                    for (unsigned int j = 0; j < M; j++) {
                        if (verbose) { if (j < 10) std::cout<<data[i][j]<<"   "; else std::cout<<data[i][j]<<"   "; }
                        else {
                            std::cout << data[i][j] << " ";
                        }
                    }
                    std::cout << std::endl;
                }
            }
        }

        void LoadFromFile(std::ifstream& is) {
            for (unsigned int i = 0; i < N; i++) {
                for (unsigned int j = 0; j < M; j++) {
                    char ch;
                    if (is >> ch) {
                        data[i][j] = static_cast<T>(ch);
                    }
                }
            }
        }

        void WriteToFile(std::fstream& os, std::string delimiter = " ", std::string addDelim = "") {
            for (unsigned int i = 0; i < N; i++) {
                for (unsigned int j = 0; j < M; j++) {
                if (j != M - 1)
                    os << data[i][j] << delimiter << addDelim;
                else
                    os << data[i][j];
                }
                os << std::endl;
            }
        }

        void Set(const unsigned int i, const unsigned int j,const T& x) {
            data[i][j] = x;
        }

        T Get(const unsigned int i, const unsigned int j) const {
            return data[i][j];
        }
        
        T* GetPtr(const unsigned int i, const unsigned int j) const {
            return &data[i][j];
        }

        unsigned int GetN() const {
            return N;
        }

        unsigned int GetM() const {
            return M;
        }
};

#endif
