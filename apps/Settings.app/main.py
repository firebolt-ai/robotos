# from PyQt5.QtWidgets import QApplication, QLabel, QWidget, QPushButton, QVBoxLayout
from PyQt5.QtWidgets import *
app = QApplication([])
window = QWidget()
label = QLabel('Settings.app')
label.show()
layout = QVBoxLayout()
layout.addWidget(QPushButton(''))
window.setLayout(layout)
window,show()
app.exec_()