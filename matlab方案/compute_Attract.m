%��������
function [Yatx,Yaty]=compute_Attract(X,Xsum,k,angle)%�������Ϊ��ǰ���꣬Ŀ�����꣬���泣��,���������ĽǶ�
%��·���ϵ���ʱ����Ϊÿ��ʱ�̵�Xgoal
R=(X(1)-Xsum(1,1))^2+(X(2)-Xsum(1,2))^2;%·�����Ŀ��ľ���ƽ��
r=sqrt(R);%·�����Ŀ��ľ���
%deltax=Xgoal(1)-X(1);
%deltay=Xgoal(2)-X(2);
Yatx=k*r*cos(angle);%angle=Y(1)
Yaty=k*r*sin(angle);
%Ҳ����������
%function y=compute_Attract(X,Xgoal,k)
%y=[Yafx,Yafy]
%������x,y����ķ�������y������
end