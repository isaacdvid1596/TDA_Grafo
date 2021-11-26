#include "dragwidget.h"
#include <iostream>
#include <string>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{    
    this->grafoActual="Normal";
    this->listaCirculosGrafo = new Lista<circuloVertice*>();
    this->grafoPrincipal = new Grafo();
    this->imprimir = grafoPrincipal;
    setMinimumSize(1280,720);
    setFrameStyle(QFrame::Raised | QFrame::WinPanel);
    setAcceptDrops(true);
    mostrarInfo = new infoMostrar(this);
    this->nombreVertice = new QTextEdit(this);
    this->nombreInicio = new QTextEdit(this);
    this->nombreFin = new QTextEdit(this);
    this->peso = new QTextEdit(this);
    nombreVertice->setGeometry(10,03,200,25);
    nombreVertice->setPlaceholderText("Nombre");
    nombreInicio->setGeometry(500,03,200,25);
    nombreInicio->setPlaceholderText("Vertice Inicial");
    nombreFin->setGeometry(710,03,200,25);
    nombreFin->setPlaceholderText("Vertice Final");
    peso->setGeometry(920,03,200,25);
    peso->setPlaceholderText("Peso Arista");
}

void DragWidget::handleSubmit()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar esta funcion");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->listaVertices->getSize()<1)
    {
        mensaje.setText("Tiene que haber al menos dos vertices para poder crear una arista");
        mensaje.show();
        return;
    }

    string inicio = (this->nombreInicio->toPlainText()).toStdString();
    string fin = (this->nombreFin->toPlainText()).toStdString();
    string nombrep = (this->peso->toPlainText()).toStdString();

    if(inicio=="" && fin=="" && nombrep=="")
    {
        mensaje.setText("Ingrese un vertice inicial, final y un peso para poder crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="" && fin=="" && nombrep!="")
    {
        mensaje.setText("Ingrese un vertice inicial y final para crear la arista");
        mensaje.show();
        return;
    }else if(inicio!="" && fin!="" && nombrep=="")
    {
        mensaje.setText("Ingrese un peso para crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="" && nombrep=="")
    {
        mensaje.setText("Ingrese un vertice inicial y un peso para crear la arista");
        mensaje.show();
        return;
    }else if(fin=="" && nombrep=="")
    {
        mensaje.setText("Ingrese un vertice final y un peso para crear la arista");
        mensaje.show();
        return;
    }else if(inicio=="")
    {
        mensaje.setText("Ingrese un vertice inicial para crear la arista");
        mensaje.show();
        return;
    }else if(fin=="")
    {
        mensaje.setText("Ingrese un vertice final para crear la arista");
        mensaje.show();
        return;
    }
    int n=0;
    try{
        n=atoi(nombrep.c_str());
    }catch(exception e)
    {
        return;
    }
    Vertice* primero = this->grafoPrincipal->getvertice(inicio);
    Vertice* segundo = this->grafoPrincipal->getvertice(fin);
    if(primero==nullptr && segundo==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice inicial y final");
        mensaje.show();
        return;
    }else if(primero==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice inicial");
        mensaje.show();
        return;
    }else if(segundo==nullptr)
    {
        mensaje.setText("Necesita ingresar nombre correcto de vertice final");
        mensaje.show();
        return;
    }

    bool res = this->grafoPrincipal->insertarArista(primero,segundo,n);
    if(!res)
    {
        mensaje.setText("Ya existe una Arista para esa conexion.");
        mensaje.show();
        return;
    }
    this->update();
    this->setText();
}

void DragWidget::handleSubmitDelet()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar esta funcion");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->listaVertices->getSize()<2)
    {
        mensaje.setText("Tiene que haber al menos dos vertices para poder eliminar una arista");
        mensaje.show();
        return;
    }
    string nombrep = (this->nombreInicio->toPlainText()).toStdString();
    string nombre = (this->nombreFin->toPlainText()).toStdString();

    if(nombrep=="" && nombre=="")
    {
        mensaje.setText("Ingrese una arista inicial y final");
        mensaje.show();
        return;
    }else if(nombrep=="")
    {
        mensaje.setText("Ingrese una arista inicial");
        mensaje.show();
        return;
    }else if(nombre=="")
    {
        mensaje.setText("Ingrese una arista final");
        mensaje.show();
        return;
    }
    bool primero = this->grafoPrincipal->existeVertice(nombrep);
    bool segundo = this->grafoPrincipal->existeVertice(nombre);
    if(!primero && !segundo)
    {
        mensaje.setText("No se encontro un vertice inicial y final con ese nombre");
        mensaje.show();
        return;
    }else if(!primero)
    {
        mensaje.setText("No se encontro un vertice inicial con ese nombre");
        mensaje.show();
        return;
    }else if(!segundo)
    {
        mensaje.setText("No se encontro un vertice final con ese nombre");
        mensaje.show();
        return;
    }
    bool res = this->grafoPrincipal->eliminarArista(nombrep,nombre);
    if(!res)
    {
        mensaje.setText("No se encontro la Arista a eliminar.");
        mensaje.show();
        return;
    }
    update();
    this->setText();
}

void DragWidget::handleSubmitDeletVertie()
{
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para habilitar esta funcion");
        mensaje.show();
        return;
    }
    string nombre = (this->nombreVertice->toPlainText()).toStdString();

    if(nombre=="")
    {
        mensaje.setText("Ingrese un nombre de vertice");
        mensaje.show();
        return;
    }

    Vertice* primero = this->grafoPrincipal->getvertice(nombre);
    if(primero==nullptr)
    {
        mensaje.setText("No se encontro un vertice con ese nombre");
        mensaje.show();
        return;
    }

    bool res = this->grafoPrincipal->eliminarVertice(nombre);
    if(!res)
    {
        mensaje.setText("No se encontro el Vertice a eliminar.");
        mensaje.show();
        return;
    }
    update();
    this->setText();
}

void DragWidget::setText()
{   this->nombreVertice->setText("");
    this->nombreInicio->setText("");
    this->nombreFin->setText("");
    this->peso->setText("");
}

void DragWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->pos().y()<130)
        return;
    if(this->imprimir!=this->grafoPrincipal)
    {
        mensaje.setText("Tiene que estar en el grafo principal para poder crear un vertice");
        mensaje.show();
        return;
    }
    string nombre = (this->nombreVertice->toPlainText()).toStdString();
    if(nombre=="")
    {
        mensaje.setText("Ingrese un nombre para poder crear un vertice");
        mensaje.show();
        return;
    }else if(this->grafoPrincipal->existeVertice(nombre))
    {
        mensaje.setText("Ya existe un vertice con ese nombre");
        mensaje.show();
        return;
    }
    this->grafoPrincipal->insertarVertice(nombre);
    Vertice* nuevo = this->grafoPrincipal->getvertice(nombre);
    if(nuevo==nullptr || nombre=="")
        return;
    QPoint q= event->pos();
    circuloVertice* c= new circuloVertice();
    c->createVertice(nombre,(q.x()-25),(q.y()-25));
    c->representavertice=nuevo;
    nuevo->dibujado=c;
    this->listaCirculosGrafo->guardar(c);
    update();
    this->setText();
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos=event->pos();
    if(pos.x()>945 && pos.x()<1005 && pos.y()>35 && pos.y()<55)
    {
        this->handleSubmit();
    }else if(pos.x()>1035 && pos.x()<1095 && pos.y()>35 && pos.y()<55)
    {
        this->handleSubmitDelet();
    }else if(pos.x()>220 && pos.x()<280 && pos.y()>3 && pos.y()<23)
    {
        this->handleSubmitDeletVertie();
    }
    else if(pos.x()>240 && pos.x()<320 && pos.y()>35 && pos.y()<55)
    {
        this->getGrado();
    }
    else if(pos.x()>10 && pos.x()<90 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToPrincipal();
    }
    else if(pos.x()>150 && pos.x()<230 && pos.y()>35 && pos.y()<55)
    {
        this->grafoToDjikstra();
    }
}

void DragWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.drawText(330,20,"Grafo Actual: " + this->grafoActual);

    painter.drawLine(0,80,1300,80);

    painter.drawRect(10,35,80,20);
    painter.drawText(32,50,"Normal");

    painter.drawRect(150,35,80,20);
    painter.drawText(170,50,"Dijkstra");

    painter.drawRect(240,35,80,20);
    painter.drawText(260,50,"Grado");

    painter.drawRect(240,3,80,20);
    painter.drawText(260,18,"Eliminar");

    painter.drawRect(945,35,80,20);
    painter.drawText(955,50,"Insertar");

    painter.drawRect(1035,35,80,20);
    painter.drawText(1045,50,"Eliminar");

    int x1,x2,y1,y2,textX,textY;
    painter.setPen(Qt::red);    
    Nodo<Vertice*>* temporal = this->imprimir->listaVertices->getFirst();
    Nodo<Arista*>* aristaTemporal;
    double ang1;
    while(temporal!=nullptr)
    {
        aristaTemporal = temporal->valor->aristas->getFirst();
        while(aristaTemporal!=nullptr)
        {
            painter.setPen(Qt::black);
            x1=temporal->valor->dibujado->x+25;
            y1=temporal->valor->dibujado->y+25;
            x2= aristaTemporal->valor->verticeFinal->dibujado->x+25;
            y2= aristaTemporal->valor->verticeFinal->dibujado->y+25;
            textX=(x1+x2)/2;
            textY=(y1+y2)/2;
            if(x1!=x2 || y1!=y2)
            {
                ang1=qAtan2((y2-y1),(x2-x1));
                QPoint ellipse1,ellipse2;
                ellipse1.setX((x2-25*qCos(ang1)));
                ellipse1.setY((y2-25*qSin(ang1)));
                ellipse2.setX((x1+25*qCos(ang1)));
                ellipse2.setY((y1+25*qSin(ang1)));
                painter.drawLine(x1,y1,x2,y2);
                painter.setPen(Qt::red);
                painter.setBrush(Qt::red);
                painter.drawEllipse(ellipse1,5,5);
                QString name= QString::fromStdString(to_string(aristaTemporal->valor->peso));
                painter.setPen(Qt::black);
                painter.drawText(textX+2,textY-2,name);
            }
            aristaTemporal = aristaTemporal->siguiente;
        }
        temporal = temporal->siguiente;
    }


    temporal=this->imprimir->listaVertices->getFirst();
    while(temporal!=nullptr)
    {
        painter.setPen(Qt::blue);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(temporal->valor->dibujado->x,temporal->valor->dibujado->y,50,50);
        painter.setPen(Qt::black);
        QString name= QString::fromStdString(temporal->valor->dibujado->name);
        painter.drawText(temporal->valor->dibujado->x-12.5,temporal->valor->dibujado->y-12.5,name);

        temporal=temporal->siguiente;
    }

}

void DragWidget::getGrado()
{
    string nombrep = (this->nombreVertice->toPlainText()).toStdString();

    if(this->grafoPrincipal->listaVertices->getSize()==0)
    {
        mensaje.setText("Necesita tener por lo menos un vertice para poder encontrar grado");
        mensaje.show();
        return;
    }else if(nombrep=="")
    {
        mensaje.setText("Ingrese el nombre de un vertice existente");
        mensaje.show();
        return;
    }

    if(!this->grafoPrincipal->existeVertice(nombrep))
    {
        mensaje.setText("Ingrese un nombre de vertice existente para poder encontrar grado");
        mensaje.show();
        return;
    }
    int grado = this->grafoPrincipal->cantidadGrado(this->grafoPrincipal->getvertice(nombrep));
    std::string gcant = std::to_string(grado);
    this->mensaje.setText("El grado del vertice es: " + QString::fromStdString(gcant));
    this->mensaje.show();


}

void DragWidget::grafoToPrincipal()
{
    this->grafoActual="Normal";
    this->imprimir=this->grafoPrincipal;
    this->update();
}

void DragWidget::grafoToDjikstra()
{
    this->grafoDijkstra = new Grafo();
    string nombrep = (this->nombreVertice->toPlainText()).toStdString();

    if(this->grafoPrincipal->listaVertices->getSize()==0)
    {
        mensaje.setText("Necesita tener por lo menos un vertice para poder ejecutar Dijkstra");
        mensaje.show();
        return;
    }else if(nombrep=="")
    {
        mensaje.setText("Ingrese un vertice inicial para ejecutar Dijkstra");
        mensaje.show();
        return;
    }

    if(!this->grafoPrincipal->existeVertice(nombrep))
    {
        mensaje.setText("Ingrese un nombre de vertice existente para poder ejecutar Dijkstra");
        mensaje.show();
        return;
    }

    arrayD= new ArrayListP<Vertice*>();
    if(this->grafoPrincipal->listaVertices->getSize()==0)
        return;
    bool visitado[this->grafoPrincipal->listaVertices->getSize()];
    int peso[this->grafoPrincipal->listaVertices->getSize()];
    Nodo<Vertice*>* temporal = this->grafoPrincipal->listaVertices->getFirst();
    Vertice*nuevo;

    while(temporal!=nullptr)
    {
        nuevo= new Vertice();
        nuevo->dibujado=temporal->valor->dibujado;
        nuevo->nombre=temporal->valor->nombre;
        arrayD->guardar(nuevo);
        temporal=temporal->siguiente;
    }

    int max = 2147483647;
    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        visitado[i]=false;
        peso[i]=max;
    }

    Vertice* caminoInicio = new Vertice();
    caminoInicio = this->grafoPrincipal->getvertice(nombrep);
    int pos=arrayD->getPos(caminoInicio);
    visitado[pos]=true;
    Nodo<Arista*>* actualizando;
    Vertice*uGrafoPrincipalU;
    Vertice* uU = new Vertice();
    Vertice* buscar2 = new Vertice();
    int posFinal;
    actualizando=caminoInicio->aristas->getFirst();

    while(actualizando!=nullptr)
    {
        uU->nombre=actualizando->valor->verticeFinal->nombre;
        posFinal=this->arrayD->getPos(uU);
        peso[posFinal]=actualizando->valor->peso;
        actualizando=actualizando->siguiente;
    }

    int menor=pos,posicionfinal,pesoNuevo,peso1,peso2;
    Nodo<Arista*>* aristaRelajadora;

    for(int i=0;i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        for(int j=0;j<this->grafoPrincipal->listaVertices->getSize();j++)
        {
            peso1=peso[j];
            for(int k=0;k<this->grafoPrincipal->listaVertices->getSize();k++)
            {
                peso2=peso[k];
                if(peso1<peso2 && !visitado[j])
                {
                    menor=j;
                }
            }
        }

        uU=arrayD->buscar(menor);
        visitado[menor]=true;

        uGrafoPrincipalU=this->grafoPrincipal->getvertice(uU->nombre);
        aristaRelajadora=uGrafoPrincipalU->aristas->getFirst();

        while(aristaRelajadora!=nullptr)
        {
            buscar2->nombre=aristaRelajadora->valor->verticeFinal->nombre;
            posicionfinal=arrayD->getPos(buscar2);
            pesoNuevo=peso[menor]+aristaRelajadora->valor->peso;
            if(peso[posicionfinal]>pesoNuevo)
            {
                peso[posicionfinal]=pesoNuevo;
            }
            aristaRelajadora= aristaRelajadora->siguiente;
        }
    }

    Vertice* paraCopiar,*finalCopiar,*devuelto;

    for(int i=0; i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        paraCopiar=arrayD->buscar(i);
        this->grafoDijkstra->insertarVertice(paraCopiar->nombre);
        devuelto=this->grafoDijkstra->getvertice(paraCopiar->nombre);
        devuelto->dibujado=paraCopiar->dibujado;
    }

    paraCopiar=this->grafoDijkstra->getvertice(nombrep);
    for(int i=0; i<this->grafoPrincipal->listaVertices->getSize();i++)
    {
        if(peso[i]!=max)
        {
            finalCopiar=arrayD->buscar(i);
            this->grafoDijkstra->insertarArista(paraCopiar->nombre,finalCopiar->nombre,peso[i]);
        }
    }

    this->grafoActual="Dijkstra";
    this->imprimir=grafoDijkstra;
    update();
}
