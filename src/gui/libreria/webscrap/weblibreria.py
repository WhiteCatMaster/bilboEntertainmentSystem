import requests
from bs4 import BeautifulSoup
import sys

URL = "https://www.casadellibro.com/?srsltid=AfmBOopELpsddHwbVms7wItBQlZrH10g-4QaFZ4T5LMOIZawrNJZ3NDs"

def obtener_libros():
    """Download the page and extract book titles."""
    headers = {"User-Agent": "Mozilla/5.0"}
    response = requests.get(URL, headers=headers)

    if response.status_code != 200:
        print(f"Error {response.status_code} accessing the page")
        return []

    soup = BeautifulSoup(response.text, "html.parser")
    peliculas = [h2.text.strip() for h2 in soup.find_all(class_ = "txtNegXXL m5")]

    return peliculas

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "--titulos":
        libros = obtener_libros()
        for libro in libros:
            print(libro)