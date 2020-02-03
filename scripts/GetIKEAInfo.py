#!/usr/bin/env python

__author__ = "Valentin Michelet"
__credits__ = ["Valentin Michelet"]
__license__ = "GPL"
__version__ = "0.1"
__maintainer__ = "Valentin Michelet"
__email__ = "michelet.valentin@gmail.com"
__status__ = "Production"

import urllib.parse
import urllib.request
from bs4 import BeautifulSoup
import re
import sys

def download(url):
  return urllib.request.urlopen(url).read();

# Variables
url = sys.argv[1]
page = download(url).decode('utf-8')
soup = BeautifulSoup(page, 'lxml')

# Name
name = soup.find('span', attrs={'class':'product-pip__name'}).text
print('name:'+name)

# Price
price = soup.find('span', attrs={'class':'product-pip__price__value'}).text
price = re.findall('(\d+),?(\d{2})?.*', price)[0]
pretty_price = '';
if price[1] != '':
  pretty_price = '.'.join(str(p) for p in price)
else:
  pretty_price = price[0]
print('price:'+pretty_price)

# Download image
img = soup.find('div', attrs={'class':'range-carousel__image'}).find('img')['src']
urllib.request.urlretrieve(img, '../IKEA_Picker/images/meuble.png')
