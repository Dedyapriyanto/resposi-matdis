#include <iostream>
#include <climits>  // Untuk INT_MAX
using namespace std;

const int MAX_CITIES = 100;  // Jumlah maksimum kota

// Fungsi untuk mencari simpul dengan jarak terkecil
int minDistance(int dist[], bool visited[], int n) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

// Fungsi utama Dijkstra
void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int n, int source, int dest) {
    int dist[MAX_CITIES];      // Menyimpan jarak terpendek
    bool visited[MAX_CITIES];  // Menandai apakah simpul sudah diproses
    int prev[MAX_CITIES];      // Menyimpan jalur terpendek

    // Inisialisasi
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[source] = 0;

    // Proses Dijkstra
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = true;

        // Update jarak untuk node tetangga
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Tampilkan hasil
    cout << "Jarak terpendek dari kota " << source << " ke kota " << dest << " adalah: " << dist[dest] << endl;

    // Rekonstruksi jalur
    cout << "Rute terpendek: ";
    int path[MAX_CITIES], pathIndex = 0;
    int current = dest;
    while (current != -1) {
        path[pathIndex++] = current;
        current = prev[current];
    }

    // Tampilkan jalur dari akhir ke awal
    for (int i = pathIndex - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    int n, m;
    int graph[MAX_CITIES][MAX_CITIES] = {0};  // Inisialisasi graf kosong

    cout << "Masukkan jumlah kota: ";
    cin >> n;

    cout << "Masukkan jumlah jalan: ";
    cin >> m;

    // Input jalur antar kota
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cout << "Masukkan jalan ke-" << i+1 << " (format: u v jarak): ";
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;  // Karena jalan dua arah
    }

    int source, dest;
    cout << "Masukkan kota asal: ";
    cin >> source;
    cout << "Masukkan kota tujuan: ";
    cin >> dest;

    dijkstra(graph, n, source, dest);

    return 0;
}
