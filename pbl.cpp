#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#define eps 0.00001
using namespace std;
float a[100][100], b[100][100], c[100], s[100], f[100];
int n;
// Định nghĩa cấu trúc Node cho danh sách liên kết đơn
struct Node
{
          int data;
          Node *next;
};

// Hàm chèn một phần tử vào danh sách liên kết đơn
void insert(Node **head, int data)
{
          Node *newNode = new Node;
          newNode->data = data;
          newNode->next = nullptr;

          if (*head == nullptr)
          {
                    *head = newNode;
          }
          else
          {
                    Node *current = *head;
                    while (current->next != nullptr)
                    {
                              current = current->next;
                    }
                    current->next = newNode;
          }
}

// Hàm chèn một phần tử vào danh sách liên kết đơn tại vị trí M/2 bằng cách nhập từ bàn phím
void insertAtIndex(Node **head, int data, int index)
{
          if (index == 0)
          {
                    Node *newNode = new Node;
                    newNode->data = data;
                    newNode->next = *head;
                    *head = newNode;
          }
          else
          {
                    Node *current = *head;
                    int i = 0;
                    while (i < index - 1 && current != nullptr)
                    {
                              current = current->next;
                              i++;
                    }
                    if (current != nullptr)
                    {
                              Node *newNode = new Node;
                              newNode->data = data;
                              newNode->next = current->next;
                              current->next = newNode;
                    }
          }
}

// Hàm in danh sách liên kết đơn
void printList(Node *head)
{
          Node *current = head;
          while (current != nullptr)
          {
                    cout << current->data << " ";
                    current = current->next;
          }
          cout << endl;
}

// Hàm in ma trận
void printMatrix(Node **matrix, int size)
{
          for (int i = 0; i < size; i++)
          {
                    printList(matrix[i]);
          }
}

int convertNodeToNumber(Node *node)
{
          return node->data;
}

// Hàm lấy ra các phần tử của ma trận và lưu vào mảng
void getMatrixElements(Node **matrix, int size, int *arr, int arrSize)
{
          int index = 0;

          for (int i = 0; i < size; i++)
          {
                    Node *current = matrix[i];
                    while (current != nullptr && index < arrSize)
                    {
                              arr[index++] = current->data;
                              current = current->next;
                    }
          }
}
bool check(float s[100], float f[100])
{
          for (int i = 1; i <= n; i++)
                    if (fabs(s[i] - f[i]) > eps)
                              return false;
          return true;
}

void gan()
{
          for (int i = 1; i <= n; i++)
          {
                    f[i] = s[i];
          }
}

void xuat()
{
          for (int i = 1; i <= n; i++)
                    cout << s[i] << "   ";
          cout << endl;
}

void chuyen()
{
          for (int i = 1; i <= n; i++)
          {
                    for (int j = 1; j <= n; j++)
                              if (i == j)
                              {
                                        a[i][j] = 0;
                              }
                              else
                              {
                                        a[i][j] = -b[i][j] / b[i][i];
                              }
                    s[i] = a[i][n + 1] = c[i] / b[i][i];
          }
          for (int i = 1; i <= n; i++)
                    f[i] = 0;
}

void process()
{
          cout << "bang ket qua:\n";
          xuat();
          while (!check(s, f))
          {
                    gan();
                    for (int i = 1; i <= n; i++)
                    {
                              s[i] = 0;
                              for (int j = 1; j <= n; j++)
                                        s[i] += a[i][j] * f[j];
                              s[i] += a[i][n + 1];
                    }
                    xuat();
          }
          cout << "vay he nghiem cua phuong trinh tren la:\n";
          xuat();
}

bool kiemTra()
{
          for (int i = 1; i <= n; i++)
          {
                    float res1 = fabs(b[i][i]);
                    float res2 = 0;
                    for (int j = 1; j <= n; j++)
                              if (i != j)
                                        res2 += fabs(b[i][j]);
                    if (res1 <= res2)
                              return false;
          }
          return true;
}

int main()
{
          bool continueLoop = true;
          while (continueLoop)
          {
                    cout << "_____________Phuong Phap Tinh" << endl;
                    cout << "1.Ban muon nhap ham so o dau" << endl;
                    cout << "1.1 Nhap truc tiep tai day(an phim 1)" << endl;
                    cout << "1.2 Nhap trong File(an phim 2)" << endl;
                    cout << "2.giai he phuong trinh(an phim 3) " << endl;
                    cout << "Nhan phim bat ky de thoat" << endl;
                    int x;
                    cin >> x;

                    switch (x)
                    {
                    case 1:
                    {
                              ifstream inFile("DAYSO.IN");
                              if (!inFile)
                              {
                                        cout << "Khong the mo file DAYSO.IN" << endl;
                                        return 1;
                              }

                              int N;
                              inFile >> N;

                              Node **matrix = new Node *[N];
                              for (int i = 0; i < N; i++)
                              {
                                        matrix[i] = nullptr;
                                        for (int j = 0; j < N - 1; j++)
                                        {
                                                  int data;
                                                  inFile >> data;
                                                  insert(&matrix[i], data);
                                        }
                              }
                              inFile.close();

                              // Thêm phần tử vào mỗi danh sách
                              for (int i = 0; i < N; i++)
                              {
                                        int roundIndex = (N - 1) / 2;
                                        if ((N - 1) % 2 != 0)
                                        {
                                                  roundIndex++;
                                        }
                                        int a;
                                        cout << "Nhap gia tri muon chen: ";
                                        cin >> a;
                                        insertAtIndex(&matrix[i], a, roundIndex);
                              }

                              // In ma trận
                              printMatrix(matrix, N);
                              //
                              // In danh sách và lưu vào file RESULT1.OUT
                              std::ofstream result1File("RESULT1.OUT");
                              if (result1File)
                              {
                                        for (int i = 0; i < N; i++)
                                        {
                                                  // printList(matrix[i]);
                                                  Node *current = matrix[i];
                                                  while (current != nullptr)
                                                  {
                                                            result1File << current->data << " ";
                                                            current = current->next;
                                                  }
                                                  result1File << std::endl;
                                        }
                                        result1File.close();
                              }
                              else
                              {
                                        std::cout << "Khong the mo file RESULT1.OUT" << std::endl;
                              }

                              // Giải phóng bộ nhớ
                              for (int i = 0; i < N; i++)
                              {
                                        Node *current = matrix[i];
                                        while (current != nullptr)
                                        {
                                                  Node *temp = current;
                                                  current = current->next;
                                                  delete temp;
                                        }
                              }
                              delete[] matrix;
                    }
                    break;
                    case 2:
                    {
                              ifstream inFile1("DAYSO.IN");
                              if (!inFile1)
                              {
                                        cout << "Khong the mo file DAYSO.IN" << endl;
                                        return 1;
                              }

                              int N;
                              inFile1 >> N;

                              Node **matrix = new Node *[N];
                              for (int i = 0; i < N; i++)
                              {
                                        matrix[i] = nullptr;
                                        for (int j = 0; j < N - 1; j++)
                                        {
                                                  int data;
                                                  inFile1 >> data;
                                                  insert(&matrix[i], data);
                                        }
                              }
                              inFile1.close();
                              const int MAX_ELEMENTS = 100;     // Số lượng phần tử tối đa trong mảng
                              int matrixElements[MAX_ELEMENTS]; // Mảng để lưu các phần tử của ma trận

                              // Lấy các phần tử của ma trận và lưu vào mảng
                              getMatrixElements(matrix, N, matrixElements, MAX_ELEMENTS);

                              // Thêm phần tử vào mỗi danh sách
                              for (int i = 0; i < N; i++)
                              {
                                        int roundIndex = (N - 1) / 2;
                                        if ((N - 1) % 2 != 0)
                                        {
                                                  roundIndex++;
                                        }
                                        int a;
                                        int randomIndex = rand() % (N * (N - 1));
                                        a = matrixElements[randomIndex];
                                        insertAtIndex(&matrix[i], a, roundIndex);
                              }

                              // In ma trận

                              printMatrix(matrix, N);
                              //
                              // In danh sách và lưu vào file RESULT1.OUT
                              std::ofstream result1File("RESULT1.OUT");
                              if (result1File)
                              {
                                        for (int i = 0; i < N; i++)
                                        {
                                                  // printList(matrix[i]);
                                                  Node *current = matrix[i];
                                                  while (current != nullptr)
                                                  {
                                                            result1File << current->data << " ";
                                                            current = current->next;
                                                  }
                                                  result1File << std::endl;
                                        }
                                        result1File.close();
                              }
                              else
                              {
                                        std::cout << "Khong the mo file RESULT1.OUT" << std::endl;
                              }
                              // Giải phóng bộ nhớ
                              for (int i = 0; i < N; i++)
                              {
                                        Node *current = matrix[i];
                                        while (current != nullptr)
                                        {
                                                  Node *temp = current;
                                                  current = current->next;
                                                  delete temp;
                                        }
                              }
                              delete[] matrix;
                              //
                    }
                    break;
                    case 3:
                    {
                              cout << "Nam dep trai vkl" << endl;
                              ifstream inFile("DAYSO.IN");
                              if (!inFile)
                              {
                                        cout << "Khong the mo file DAYSO.IN" << endl;
                                        return 1;
                              }

                              int N;
                              inFile >> N;
                              n = N;
                              ifstream inFile1("RESULT1.OUT");
                              if (inFile1.is_open())
                              {
                                        for (int i = 1; i <= N; i++)
                                        {
                                                  for (int j = 1; j <= N; j++)
                                                  {
                                                            if (!(inFile1 >> b[i][j]))
                                                            {
                                                                      // Xử lý lỗi khi không thể đọc giá trị từ tệp
                                                            }
                                                  }
                                        }
                                        inFile1.close();
                              }
                              else
                              {
                                        cout << "Khong the mo file RESULT1.OUT" << endl;
                              }
                              cout << "nhap cac phan tu cua mang B: ";
                              for (int i = 1; i <= N; i++)
                              {
                                        cin >> c[i];
                              }
                              for (int i = 1; i <= n; i++)
                              {
                                        for (int j = 1; j <= n; j++)
                                        {
                                                  cout << b[i][j] << "   ";
                                        }
                                        cout << c[i] << endl;
                              }
                              chuyen();
                              if (kiemTra())
                                        process();
                              else
                                        cout << "ban nhap he phuong trinh khong phu hop!!!";
                    }
                    break;
                    default:
                              continueLoop = false; // Thoát khỏi vòng lặp khi lựa chọn không hợp lệ
                              break;
                    }
          }
          return 0;
}
