import requests
import json
import sys

if len(sys.argv) < 2:
    print("Usage: python movies.py <movie_id>")
    sys.exit(1)

what = sys.argv[2]

url = f"https://api.themoviedb.org/3/movie/{what}?language=en-US&page=1"

headers = {
    "accept": "application/json",
    "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJhdWQiOiIzYzYxOWUwMmQyZWNlMDZkZGViZmJjMjQ5OGY2M2MwYSIsIm5iZiI6MTczOTgyMzQ4MS4yLCJzdWIiOiI2N2IzOTk3OTViOGM3ODllODQ5ZmJjMzMiLCJzY29wZXMiOlsiYXBpX3JlYWQiXSwidmVyc2lvbiI6MX0.vzE5C9Zpezyn9UT85MwfxL0b9eeQDljjUipqMDs_ui8"
}

response = requests.get(url, headers=headers)
data = response.json()  # Convierte la respuesta a JSON

# Para mostrar las películas (que están en la clave 'results')
if 'results' in data:
    for movie in data['results']:
        print(f"Titulo: {movie.get('title')}")
        #print(f"Fecha de estreno: {movie.get('release_date')}")
        #print(f"Descripción: {movie.get('overview')}")
        #print("-" * 50)  # Separador