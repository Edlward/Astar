#include"function_declare.h"
/// Function definitions  
/**
* @function showpath
*/

/*��ʾ������ͼƬ�ͽ����ĵ�ͼ�Ǹ�ת��*/
void showmap ( int map[][Width], Point & begin,Point & target, vector<vector<int>>&path_list)
{
	//��vector<vector<int>>&path_list���ݸ�vector<Point>path
	vector<Point>path;
	Point point;
	for (int i = 0; i < path_list.size(); i++)
	{
		point.x = path_list[i][0];
		point.y = path_list[i][1];
		path.push_back(point);
	}
	//���path������
	for (int i = 0; i <path.size(); i++) {
		cout << path[i] << ' ';
	}
	cout << '\n';


	Mat img(Width * ratio, Height * ratio, CV_8UC3, Scalar(255, 255, 255));//caitu

	int radius = ratio / 2;
	int lineType = 8;

	for (int j = 0; j < Height; j++)
	{
		Point center;
		for (int i = 0; i < Width; i++)
		{
			if (i == begin.x && j == begin.y)//���
			{
				center.x = i * ratio;
				center.y = j * ratio;
				circle(img, center, radius, Scalar(0, 233, 0), -1, lineType);
			}
			else if (i == target.x && j == target.y)//�յ�
			{
				center.x = i * ratio;
				center.y = j * ratio;
				circle(img, center, radius, Scalar(255, 97, 0), -1, lineType);
			}
			else if (map[i][j] == 1)//�ϰ���
			{
				// Rectangle���������� ͼƬ�� ���Ͻǣ� ���½ǣ� ��ɫ�� ������ϸ�� �������ͣ�������  
				center.x = i*ratio - ratio / 2;
				center.y = j*ratio - ratio / 2;
				rectangle(img, center, Point(center.x + ratio, center.y + ratio), Scalar(47, 79, 79), 1, 4, 0);
			}
			else
			{
			}
		}
	}
	imshow("Path Planing", img);

	for (int i = 0; i < path.size(); i++)//·����ʶ
	{
		Point center;
		waitKey(200);
		center.x = (path[i].x)*ratio;
		center.y = (path[i].y)*ratio;
		circle(img, center, ratio / 4, Scalar(127, 255, 121), -1, lineType);
		imshow("Path Planing", img);
	}

}