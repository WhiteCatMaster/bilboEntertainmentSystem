import requests
from bs4 import BeautifulSoup
import sys

URL = "https://www.golem.es/golem/golem-alhondiga"

def obtener_peliculas():
    """Download the page and extract movie titles."""
    headers = {"User-Agent": "Mozilla/5.0"}
    response = requests.get(URL, headers=headers)

    if response.status_code != 200:
        print(f"Error {response.status_code} accessing the page")
        return []

    soup = BeautifulSoup(response.text, "html.parser")
    peliculas = [h2.text.strip() for h2 in soup.find_all(class_ = "txtNegXXL m5")]
    horas = [h2.text.strip() for h2 in soup.find_all(class_ = "horaXXXL")]

    return peliculas

if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "--titulos":
        peliculas = obtener_peliculas()
        for pelicula in peliculas:
            print(pelicula)
    if len(sys.argv) > 1 and sys.argv[1] == "--horas":
        horas = obtener_peliculas()
        for hora in horas:
            print(hora)