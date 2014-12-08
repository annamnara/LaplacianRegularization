W=load('weight.txt');
D=zeros(500);
for i=1:size(W,2)
    D(i,i)=sum(W(i,:));
end

L=D-W;
[U V]=eig(L);
evals=diag(V);
evalssor=sort(evals);