#!/usr/bin/env python

"""
    Pdf 
    tipo 1 -> inicio *** contenido->ruta donde se guardara del pdf
    tipo 2 -> titulo *** contenido->titulo del reporte
    tipo 3 -> texto  *** contenido->texto simple
    tipo 4 -> imagen *** contenido->ruta y nombre de la imagen
    tipo 5 -> conjunto de imagenes *** contenido -> ruta de las imagenes
    tipo 6 -> fin    *** contenido->puede ir vacio
"""

import rospy
import time
from std_msgs.msg import String
from justina_tools.msg import Pdf
from pdfdocument.document import PDFDocument
from reportlab.pdfgen import canvas
from reportlab.platypus import Image
from os import path
import os

global pdf

def creaPdf(ruta):
	"""
	Crea un PDF simple en la ruta indicada con nombre dado por la fecha y hora actuales
	"""
	global pdf
	existe = path.exists(ruta)	
	if not existe:
		print "La ruta no existe, se guardara en el directorio actual"
		ruta = "."
	archivo = ruta +"/Report-" + time.strftime("%d%m%y-%H%M%S")+".pdf"	
	pdf = PDFDocument(archivo)
	pdf.init_report()
	print "Guardando en " + archivo

def tituloPdf(titulo):
	"""
	Agrega un titulo al PDF abierto con subrayado
	"""
	global pdf
	pdf.h1(titulo)
	pdf.hr()

def textoPdf(texto):
	"""
	Agrega texto simple al PDF
	"""
	global pdf
	rospy.loginfo('El dato a guardar es: %s', texto)
	pdf.p(texto)

def terminaPdf():
	"""
	Termina y genera el PDF
	"""
	global pdf
	pdf.generate()
	print "Terminando pdf"

def imagenPdf(rutaTotal):
	"""
	Agrega una imagen dada por la ruta y nombre indicados en rutaTotal
	"""
	global pdf
	existe = path.exists(rutaTotal)	
	if not existe:
		print "La imagen no se encuentra en %s" % rutaTotal 
		pdf.p("*****Image not found at %s *****\n\n\n" % rutaTotal)
	else :
		ruta, archivo = path.split(rutaTotal)
		pdf.append(Image(rutaTotal, width=320, height=240, hAlign='CENTER'))
		pdf.generate_style()
		pdf.p("%s \n\n"  % archivo, style=pdf.style.bold)

def imagenesPdf(rutaArchivos):
	"""
	Agrega todas las imagenes contenidas en la ruta y nombre indicados en rutaArchivos
	"""
	global pdf
	existe = path.exists(rutaArchivos)
	if not existe :
		print "La ruta de las imagenes no existe : %s" % rutaArchivos
		pdf.p("*****Images not found at %s*****\n\n\n" % rutaArchivos)
	else :
		archivos = os.listdir(rutaArchivos)
		for nombreArchivo in archivos:
			rutaImagen = rutaArchivos + nombreArchivo
			if os.path.isfile(rutaImagen):
				pdf.append(Image(rutaImagen, width=320, height=240, hAlign='CENTER'))
				pdf.generate_style()
				pdf.p("%s \n\n"  % nombreArchivo, style=pdf.style.bold)


def callback(data):
	"""
	Para decidir la accion con base en el tipo de mensaje recibido
	"""
	try:
		if data.tipo == 1:
			creaPdf(data.contenido)
		elif data.tipo == 2:
			tituloPdf(data.contenido)
		elif data.tipo == 3:
			textoPdf(data.contenido)
		elif data.tipo == 4:
			imagenPdf(data.contenido)
		elif data.tipo == 5:
			imagenesPdf(data.contenido)
		elif data.tipo == 6:
			terminaPdf()
		else:
			print "Tipo de mensaje PDF no valido"
	except IOError as ex:
		print ex.__class__, ex.__doc__, ex.message
		print "****Hubo un problema al guardar el archivo********"
	except Exception as ex:
		print ex.__class__, ex.__doc__, ex.message
		template = "Una excepcion de tipo {0} ocurrio. Arguments:\n{1!r}"
		message = template.format(type(ex).__name__, ex.args)
		print message

def listener(): 
	rospy.init_node('genera_pdf', anonymous=True)
	rospy.Subscriber('pdf_topic', Pdf, callback)
	rospy.spin()

if __name__ == '__main__':	
	global pdf
	print "INICIALIZANDO GENERADOR DE PDF ..."
	listener()
