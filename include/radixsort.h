
#include <cstdint>
#include <iostream>
#include <math.h>

namespace edu {
    namespace vcccd {
        namespace vc {
            namespace csv15 {

                template<typename T>
                int getdigits(T number) {
                    if (number == 0) {
                        return (1);
                    }
                    else {
                        int numdig = 0;
                        while (number != 0) {
                            numdig++;
                            number /= 10;
                        }

                        return(numdig);
                    }
                }

                template<typename T>
                int maxdigits(T array[], size_t size) {
                    int maximum = 0;
                    for (int i = 0; i < size; i++) {
                        int temp = getdigits(array[i]);
                        if (temp > maximum) {
                            maximum = temp;
                        }
                    }
                    return(maximum);

                }


                //int overload
                int lowdig(int number, int pow) {
                    return(abs((number / pow) % 10));
                }

                //templated overload
                template<typename T>
                int lowdig(T number, int pow) {
                    return((number / pow) % 10);
                }

                template<typename T>
                void append(T** buckets, int index, T number, size_t size) {
                    int place = 0;
                    while ((buckets[index][place] != NULL) && place < size) {
                        place += 1;
                    }
                    buckets[index][place] = number;
                }

                template<typename T>
                void makeNull(T** buckets, size_t width, size_t height) {
                    for (int i = 0; i < width; i++) {
                        buckets[i] = new T[height];
                        for (int j = 0; j < height; j++) {
                            buckets[i][j] = NULL;
                        }
                    }
                }

                template<typename T>
                void clear(T** buckets, size_t width) {
                    //delete "buckets"
                    for (int i = 0; i < width; i++) {
                        delete[] buckets[i];
                    }
                    delete[] buckets;
                    buckets = NULL;



                }

                //Debug functions
                template<typename T>
                void printarray(T array[], size_t size) {
                    //Debug: print unsorted input array
                    std::cout << "array: ";
                    for (int i = 0; i < size; i++) {
                        std::cout << array[i] << "  ";
                    }
                    std::cout << "\n \n";
                }

                template<typename T>
                void printBuckets(T** buckets, size_t width, size_t height) {
                    //Debug: print buckets, no values given
                    std::cout << "buckets, empty:" << std::endl;
                    for (int i = 0; i < width; i++) {
                        std::cout << " bucket " << i << ": ";
                        for (int j = 0; j < height; j++) {
                            std::cout << " [" << buckets[i][j] << "] ";
                        }
                        std::cout << std::endl;
                        std::cout << std::endl;

                    }
                }

                template<typename T>
                int checknull(T array[]) {
                    if (array == nullptr) {
                        return(-1);
                    }
                    return(1);
                }

                template<typename T>
                void radixsort(T array[], size_t size) {
                    int check = checknull(array);
                    if (check == -1) {
                        std::cout << "array is Null" << std::endl;
                        return;
                    }

                    std::cout << "unsorted:" << std::endl;
                    //Debug: print unsorted input array
                    printarray(array, size);

                    int max = maxdigits(array, size);
                    //Debug
                    std::cout << "max = " << max << std::endl;

                    int pow10 = (int)pow(10, 0);
                    //Debug
                    std::cout << "pow10 = " << pow10 << std::endl;


                    //Initialize dynamic multidimensional array
                    size_t width = 10;
                    size_t height = size;


                    for (int digCount = 0; digCount < max; digCount++) {
                        T **buckets = new T *[width];
                        makeNull(buckets, width, height);



                        std::cout << "pow10 = " << pow10 << std::endl;
                        for (int i = 0; i < size; i++) {
                            int buckPlace = lowdig(array[i], pow10);
                            append(buckets, buckPlace, array[i], size);
                        }

                        int arrayInd = 0;
                        for (int i = 0; i < 10; i++) {
                            int j = 0;
                            while ((buckets[i][j] != NULL) && j < size) {
                                array[arrayInd] = buckets[i][j];
                                arrayInd++;
                                j++;
                            }
                        }

                        pow10 = pow10 * 10;
                        //DEBUG:
                        printarray(array, size);
                        printBuckets(buckets, width, height);

                        clear(buckets, width);
                        std::cout << "buckets cleared!" << std::endl;
                    }

                }
            }
        }
    }
}

