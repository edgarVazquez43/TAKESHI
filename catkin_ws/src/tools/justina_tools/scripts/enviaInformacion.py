#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from justina_tools.msg import Pdf

def mandaInformacion(ruta):
    
    
    contador = 1
    print "Comenzando"
    """
    Pdf 
    tipo 1 -> inicio *** contenido->ruta donde se guardara del pdf
    tipo 2 -> titulo *** contenido->titulo del reporte
    tipo 3 -> texto  *** contenido->texto simple
    tipo 4 -> imagen *** contenido->ruta y nombre de la imagen
    tipo 5 -> conjunto de imagenes *** contenido -> ruta de las imagenes
    tipo 6 -> fin    *** contenido->puede ir vacio
    """
    mensaje = Pdf()
    mensaje.tipo = 1
    mensaje.contenido = ruta
    rospy.loginfo(mensaje)
    pub.publish(mensaje)
    mensaje.tipo = 2
    mensaje.contenido = "Pruebas con contador"
    pub.publish(mensaje)

    while not rospy.is_shutdown():
        mensaje.tipo = 3
        mensaje.contenido = "Datos guardados desde el contador no : %s" % contador
        rospy.loginfo(mensaje)
        pub.publish(mensaje)
        contador = contador + 1
        if contador==10:
            mensaje.tipo = 6
            mensaje.contenido = ""
            rospy.loginfo(mensaje)
            pub.publish(mensaje)
            return
        rate.sleep()
    print "terminando"
    mensaje.tipo = 6
    mensaje.contenido = ""
    rospy.loginfo(mensaje)
    pub.publish(mensaje)

def mandaImagenes(ruta):
    
    
    print "Comenzando"
    """
    Pdf 
    tipo 1 -> inicio *** contenido->ruta donde se guardara del pdf
    tipo 2 -> titulo *** contenido->titulo del reporte
    tipo 3 -> texto  *** contenido->texto simple
    tipo 4 -> imagen *** contenido->ruta y nombre de la imagen
    tipo 5 -> conjunto de imagenes *** contenido -> ruta de las imagenes
    tipo 6 -> fin    *** contenido->puede ir vacio
    """
    mensaje = Pdf()
    mensaje.tipo = 1
    mensaje.contenido = ruta
    rospy.loginfo(mensaje)
    pub.publish(mensaje)
    mensaje.tipo = 2
    mensaje.contenido = "Pruebas con imagen"
    pub.publish(mensaje)
    contador =  1
    while not rospy.is_shutdown():
        mensaje.tipo = 3
        mensaje.contenido = "Probando con una imagen\n\n\n" 
        rospy.loginfo(mensaje)
        pub.publish(mensaje)

        mensaje.tipo = 4
        mensaje.contenido = "/home/hsr_pumas/objs/orange.png" 
        rospy.loginfo(mensaje)
        pub.publish(mensaje)
        
        mensaje.tipo = 3
        mensaje.contenido = "Probando con conjunto de imagenes\n\n\n" 
        rospy.loginfo(mensaje)
        pub.publish(mensaje)

        mensaje.tipo = 5
        mensaje.contenido = "/home/hsr_pumas/objs/" 
        rospy.loginfo(mensaje)
        pub.publish(mensaje)
        

        contador = contador + 1
        if contador==2:
            mensaje.tipo = 6
            mensaje.contenido = ""
            rospy.loginfo(mensaje)
            pub.publish(mensaje)
            return
        rate.sleep()
    print "terminando"
    mensaje.tipo = 6
    mensaje.contenido = ""
    rospy.loginfo(mensaje)
    pub.publish(mensaje)

if __name__ == '__main__':
    pub = rospy.Publisher('pdf_topic', Pdf, queue_size=10)
    rospy.init_node('envia_informacion', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    
    try:
        mandaInformacion("/home/hsr_pumas/test_pdfs")
        mandaImagenes("/home/hsr_pumas/test_pdfs")
    except rospy.ROSInterruptException:   
        print "Hubo una excepcion"
        pass
