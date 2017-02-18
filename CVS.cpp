#include <iostream>
#include <fstream>
#include <deque>
/*
    Funciones para la interpolacion de Lagrange
    * float L(int i, float t, std::deque<int> x)
        -> i: Posicion dentro de los puntos en x para no tomar dicho valor en el interpolador
        -> t: Punto a interpolar
        -> x: Valores de la coordenada x dada por los puntos
    * float Lagrange(float t, std::deque<int> x, std::deque<int> y)
        -> t: Punto en x para interpolar
        -> x: Valores de la coordenada x dada por los puntos
        -> y: Valores de la coordenada y dada por los puntos
*/
float L(int i, float t, std::deque<float> x);
float Lagrange(float t, std::deque<float> x, std::deque<float> y);

int main (int argc, char* argv[])
{
    //Estructuras para guardar los puntos dados en X y Y
    std::deque<float> x, y;
    //Estructura para guardar los puntos interpolados
    std::deque<float> answerX, answerY;
    //Valor donde empiece la interpolacion
    float rangeBegin = 1;
    //Valor donde termine la interpolacion
    float rangeEnd = 168;
    //Incremento entre cada uno de los puntos que se den para la interpolacion
    float increment = 1;
    /*
        Verificacion de los parametros del main para que se incluya
        el nombre del archivo para leer los puntos dados de X y Y
        y ademas donde se escribiran los datos de salida
    */
    if(argc != 3)
    {
        std::cout << "Faltan parametros para la ejecucion del programa." << std::endl;
        return(-1);
    }
    //Variable del archivo y apertura del mismo
    std::ifstream file(argv[1]);
    //Variable del archivo de salida y apertura del mismo
    std::ofstream outputFile(argv[2]);
    /*
        Verificacion de la apertura correcta del archivo de entrada dado
        y del archivo de salida
    */
    if(!file.is_open() && !outputFile.is_open())
    {
        std::cout << "No se pudo abrir el archivo de entrada o salida indicado." << std::endl;
        return(-2);
    }
    //Lectura de los datos del archivo para llenar las estructuras de X y Y
    float X, Y;
    char comma;
    do
    {
        file >> X >> comma >> Y;
        std::cout << X << "->" << Y << std::endl;
        x.push_back(X);
        y.push_back(Y);
    }while(!file.eof());
    x.pop_back();
    y.pop_back();
    //Fin lectura del archivo de entrada
    std::cout << "Tamanio x: " << x.size() << std::endl;
    std::cout << "Tamanio y: " << y.size() << std::endl;
    //Variable para el valor calculado de Y
    float calculatedY;
    //Ciclo para el rango de puntos que se den
    for(float i = rangeBegin; i <= rangeEnd; i += increment)
    {
        //Adicion del punto a la respuesta de X
        answerX.push_back(i);
        //Calculando la interpolacion en el punto i
        calculatedY = Lagrange(i, x, y);
        //Adicion del punto calculado a la respuesta Y
        answerY.push_back(calculatedY);
    }
    //Iteradores para recorrer las respuestas generadas
    std::deque<float>::iterator itX = answerX.begin();
    std::deque<float>::iterator itY = answerY.begin();
    //Escritura del archivo de salida
    for(; itX != answerX.end() && itY != answerY.end(); itX++, itY++){
        outputFile << *itX << "," << *itY << std::endl;
    }
    //Cierre de los archivos utilizados
    file.close();
    outputFile.close();
    return 0;
}
/*
    Funcion para la interpolacion de Lagrange
    * float L(int i, float t, std::deque<int> x)
        -> i: Posicion dentro de los puntos en x para no tomar dicho valor en el interpolador
        -> t: Punto a interpolar
        -> x: Valores de la coordenada x dada por los puntos
*/
float L(int i, float t, std::deque<float> x)
{
    float result = 1;
    for(int j = 0; j < x.size(); j++)
    {
        if(j != i)
            result *= (t - x[j]*24) / (x[i]*24 - x[j]*24);
    }
    return result;
}
/*
    Funcion para la interpolacion de Lagrange
    * float Lagrange(float t, std::deque<int> x, std::deque<int> y)
        -> t: Punto en x para interpolar
        -> x: Valores de la coordenada x dada por los puntos
        -> y: Valores de la coordenada y dada por los puntos
*/
float Lagrange(float t, std::deque<float> x, std::deque<float> y)
{
    float result;
    for(int i = 0; i < x.size(); i++)
    {
        result += y[i] * L(i, t, x);
    }
    return result;
}

float maximo( int dia, std::deque<float> answerX, std::deque<float> answerY )
{
  int finDia = dia * 24;
  int inicioDia = dia - 24;
  float maximo = answerY[ inicioDia ];
  inicioDia++;
  for( inicioDia; inicioDia < finDia; inicioDia++ )
  {
    if( maximo < answerY[ inicioDia ] )
    {
      maximo = answerY;
    }
  }
}
