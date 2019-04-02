clear
%Persamaan  f(x)=(x1^2+x2-11)^2+(x1+x2^2-7)^2
%Batas   -5.12<=x1<=5.12 dan -5.12<=x2<=5.12
BA=5.12;
BB=-5.12;
%1. Bangkitkan Populasi
solusi=zeros(4,16);
optimum=100;
while optimum>0.1
for i=1:4
    random=round(rand()*65535);
    %encode
    solusi(i,:)=de2bi(random,16);  
end
solusi;
%decode
 for i=1:4
 solusi_dec(i,1)=128*solusi(i,1)+64*solusi(i,2)+32*solusi(i,3)+16*solusi(i,4)+8*solusi(i,5)+4*solusi(i,6)+2*solusi(i,7)+1*solusi(i,8);
 solusi_dec(i,2)=128*solusi(i,9)+64*solusi(i,10)+32*solusi(i,11)+16*solusi(i,12)+8*solusi(i,13)+4*solusi(i,14)+2*solusi(i,15)+1*solusi(i,16);
 end
solusi_dec;
solusi_dec=BB+(BA-BB)/255*solusi_dec;

%2. Evaluasi
%Hitung keluaran fungsi
for i=1:4
f(i)=(solusi_dec(i,1)^2+solusi_dec(i,2)-11)^2+(solusi_dec(i,1)+solusi_dec(i,2)^2-7)^2;
end
optimum=min(f)
%Hitung nilai fitness
for i=1:4
F(i)=1/(f(i)+0.1);
end
F;
%normalisasi
Fn(:)=(F(:)-min(F));
Fn=Fn/sum(Fn)*100;
%buat Roullete Wheel
for i=1:4
    if i==1
        rolete(i)=Fn(i);
    else
    rolete(i)=rolete(i-1)+Fn(i);
    end
end
%buat random dan tentukan solusi yg terpilih menjadi ortu
rand_seleksi=rand*100;
ortu=zeros(2,16);
for j=1:2
for i=1:4
    if rand_seleksi<rolete(i)
        terpilih=i;
        break;
    end
end
ortu(j,:)=solusi(j,:);
end
i;
ortu;
%Crossover
anak=zeros(4,16);
%crossover anak 1
anak(1,1:7)=ortu(1,1:7);
anak(1,8)=ortu(2,8);
anak(1,9:15)=ortu(1,9:15);
anak(1,16)=ortu(2,16);
%crossover anak 2
anak(2,1:7)=ortu(2,1:7);
anak(2,8)=ortu(1,8);
anak(2,9:15)=ortu(2,9:15);
anak(2,16)=ortu(1,16);
%crossover anak 3
anak(2,1:4)=ortu(2,1:4);
anak(2,5:8)=ortu(1,5:8);
anak(2,9:12)=ortu(2,9:12);
anak(2,13:16)=ortu(1,13:16);
%crossover anak 4
anak(1,1:4)=ortu(1,1:4);
anak(1,5:8)=ortu(2,5:8);
anak(1,9:12)=ortu(1,9:12);
anak(1,13:16)=ortu(2,13:16);

%mutasi
for i=1:4
    mutasi_no=round(rand*1)+1;
    anak(i,mutasi_no)=~anak(i,mutasi_no);
end
solusi=anak;
end
solusi
f