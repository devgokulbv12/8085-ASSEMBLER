#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
using namespace std;
string user_code;
string code[10];
string line;
int num =0;
struct one_byte
{
    
    char op_code[100][10]={"MOV A,A","MOV A,B","MOV A,C","MOV A,D","MOV A,E","MOV A,H","MOV A,L","MOV A,M",
                           "MOV B,A","MOV B,B","MOV B,C","MOV B,D","MOV B,E","MOV B,H","MOV B,L","MOV B,M",
                           "MOV C,A","MOV C,B","MOV C,C","MOV C,D","MOV C,E","MOV C,H","MOV C,L","MOV C,M",
                           "MOV D,A","MOV D,B","MOV D,C","MOV D,D","MOV D,E","MOV D,H","MOV D,L","MOV D,M", 
                           "MOV E,A","MOV E,B","MOV E,C","MOV E,D","MOV E,E","MOV E,H","MOV E,L","MOV E,M",
                           "MOV H,A","MOV H,B","MOV H,C","MOV H,D","MOV H,E","MOV H,H","MOV H,L","MOV H,M",
                           "MOV L,A","MOV L,B","MOV L,C","MOV L,D","MOV L,E","MOV L,H","MOV L,L","MOV L,M",
                           "MOV M,A","MOV M,B","MOV M,C","MOV M,D","MOV M,E","MOV M,H","MOV M,L","LDAX B",
                           "LDAX D","STAX B","STAX D","XCHG","RET","RNZ","RZ","RNC","RC","RPO","RPE","RP","RM"};
    
    int hex_code[100]={0x7f,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,
                       0x47,0x40,0x41,0x42,0x44,0x45,0x46,0x47,
                       0x4f,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,
                       0x57,0x50,0x51,0x52,0x53,0x54,0x55,0x56,
                       0x5f,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,
                       0x67,0x60,0x61,0x62,0x63,0x64,0x65,0x66,
                       0x6f,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,
                       0x77,0x70,0x71,0x72,0x73,0x74,0x75,0x0a,
                       0x1a,0x02,0x12,0xeb,0xc9,0xc0,0xc8,0xd0,0xd8,0xe0,0xe8,0xf0,0xf8};

    char op_code_mvi[100][8] ={"MVI A,","MVI B,","MVI C,","MVI D,","MVI E,","MVI H,","MVI L,","MVI M,","LXI B,","LXI D,","LXI H,","LXI SP,"};
    
    int hex_code_2[100]={0x3e,0x06,0x0e,0x16,0x1e,0x26,0x2e,0x36,0x01,0x11,0x21,0x31};

    char op_code_adi[100][10]={"ADI ","ACI ","SUI ","SBI ","ANI ","XRI ","ORI ","CPI ","JMP ","JNZ ","JNC ","JPO ","JPE ",
                               "CNZ ","CNC ","CPO ","CPE ","CALL","OUT ","STA ","LDA "};
    int hex_code_adi[100]={0xc6,0xce,0xd6,0xde,0xe6,0xee,0xf6,0xfe,0xc3,0xc2,0xd2,0xe2,0xea,
                           0xc4,0xd4,0xe4,0xec,0xcd,0xd3,0x32,0x3a};
    
    char op_code_flag[100][10]={"JZ ","JC ","JP ","JM ","CZ ","CC ","CP ","CM ","IN "};
    int hex_code_flag[100]={0xca,0xda,0xf2,0xfa,0xcc,0xdc,0xf4,0xfc,0xdb};

    char op_code_add[200][100]={"ADD A","ADD B","ADD C","ADD D","ADD E","ADD H","ADD L","ADD M",
                                "ADC A","ADC B","ADC C","ADC D","ADC E","ADC H","ADC L","ADC M",
                                "SUB A","SUB B","SUB C","SUB D","SUB E","SUB H","SUB L","SUB M",
                                "SBB A","SBB B","SBB C","SBB D","SBB E","SBB H","SBB L","SBB M",
                                "DAD B","DAD D","DAD H","DAD SP",
                                "INR A","INR B","INR C","INR D","INR E","INR H","INR L","INR M",
                                "DCR A","DCR B","DCR C","DCR D","DCR E","DCR H","DCR L","DCR M",
                                "INX B","INX D","INX H","INX SP",
                                "DCX B","DCX D","DCX H","DCX SP",
                                "DAA","CMA","CMC","STC",
                                "ANA A","ANA B","ANA C","ANA D","ANA E","ANA H","ANA L","ANA M",
                                "ORA A","ORA B","ORA C","ORA D","ORA E","ORA H","ORA L","ORA M",
                                "XRA A","XRA B","XRA C","XRA D","XRA E","XRA H","XRA L","XRA M",
                                "CMP A","CMP B","CMP C","CMP D","CMP E","CMP H","CMP L","CMP M",
                                "RLC","RRC","RAL","RAR","PCHL","PUSH B","PUSH D","PUSH H","PUSH PSW",
                                "XTHL","SPHL","POP B","POP D","POP H","POP PSW","EI","DI","RIM","SIM",
                                "NOP","HLT","RST 0","RST 1","RST 2","RST 3","RST 4","RST 5","RST 6","RST 7"};
    int hex_code_add[200]={0x87,0x80,0x81,0x82,0x83,0x84,0x85,0x86,
                           0x8f,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,
                           0x97,0x90,0x91,0x92,0x93,0x94,0x95,0x96,
                           0x9f,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,
                           0x09,0x19,0x29,0x39,
                           0x3c,0x04,0x0c,0x14,0x1c,0x24,0x2c,0x34,
                           0x3d,0x05,0x0d,0x15,0x1d,0x25,0x2d,0x35,
                           0x03,0x13,0x23,0x33,
                           0x0b,0x1b,0x2b,0x3b,
                           0x27,0x2f,0x3f,0x37,
                           0xa7,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,
                           0xb7,0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,
                           0xaf,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,
                           0xbf,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,
                           0x07,0x0f,0x17,0x1f,0xe9,0xc5,0xd5,0xe5,0xf5,
                           0xe3,0xf9,0xc1,0xd1,0xe1,0xf1,0xfb,0xf3,0x20,0x30,
                           0x00,0x76,0xc7,0xcf,0xd7,0xdf,0xe7,0xef,0xf7,0xff};
    
};
int stringtointeger(char value)
{
    int digit;
    digit = value;
    digit = digit - 48;
    return digit;
}
void get_string(struct one_byte object)
{
    ifstream file;
    file.open("C:\\Users\\PC\\Desktop\\assembly.txt");
    if(!file.is_open())
    {
        cout<<"Unable to open the file."<<endl;
        
    }
    
    while(getline(file, line))
    {
        code[num] = line;
        num++;
        
    }
    file.close();
    
   
}

void get_instruction()
{
    cout<<"enter op code:";
    
    getline(cin,user_code);
}
void mov(struct one_byte object)
{
   for(int i =0;i<100;i++)
    {
        if(user_code == object.op_code[i])
        {
            cout<<std::hex <<object.hex_code[i]<<endl;
        }
    }
}
void add(struct one_byte object)
{
   for(int i =0;i<200;i++)
    {
        if(user_code == object.op_code_add[i])
        {
            cout<<std::hex <<object.hex_code_add[i]<<endl;
        }
    }
}
void mvi(struct one_byte object)
{
    int i;
    for(int i =0;i<8;i++)
    {
        int flag =0;
        string compare;
        compare = object.op_code_mvi[i];
        string val = user_code;
        for(int j =0 ;j<6;j++)
        {
            if(user_code[j] != compare[j])
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            cout<<std::hex<<object.hex_code_2[i]<<endl;
            int integer;
            for(int j =6;j<8;j++)
            {
                integer = stringtointeger(user_code[j]);
                cout<<integer;
            } 
            cout<<endl;
        }
        
    }
}
void flag(struct one_byte object)
{
    int i;
    for(int i =0;i<20;i++)
    {
        int flag =0;
        string compare;
        compare = object.op_code_flag[i];
        string val = user_code;
        for(int j =0 ;j<3;j++)
        {
            if(user_code[j] != compare[j])
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            cout<<std::hex<<object.hex_code_flag[i]<<endl;
            int integer;
            for(int j =3;j<5;j++)
            {
                integer = stringtointeger(user_code[j]);
                cout<<integer;
            } 
            cout<<endl;
        }
        
    }
}
void adi(struct one_byte object)
{
    int i;
    for(int i =0;i<20;i++)
    {
        int flag =0;
        string compare;
        compare = object.op_code_adi[i];
        string val = user_code;
        for(int j =0 ;j<4;j++)
        {
            if(user_code[j] != compare[j])
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            cout<<std::hex<<object.hex_code_adi[i]<<endl;
            int integer;
            for(int j =4;j<6;j++)
            {
                integer = stringtointeger(user_code[j]);
                cout<<integer;
            } 
            cout<<endl;
        }
        
    }
}
void lxi(struct one_byte object)
{
    int i;
    for(int i =8;i<12;i++)
    {
        int flag =0;
        string compare;
        compare = object.op_code_mvi[i];
        string val = user_code;
        if(i==11)
        {
            for(int j =0;j<7;j++)
            {
                if(user_code[j]!= compare[j])
                {
                    flag =1;
                }
            }
        }
        for(int j =0 ;j<6;j++)
        {
            if(user_code[j] != compare[j])
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            cout<<std::hex<<object.hex_code_2[i]<<endl;
            int integer;
            if(i>0 && i<= 10) 
            {
                for(int j =6;j<10;j++)
                {
                    integer = stringtointeger(user_code[j]);
                    cout<<integer;
                }
            }
            else
            {
                for(int j = 7;j<11;j++)
                {
                    integer = stringtointeger(user_code[j]);
                    cout<<integer;
                }
            }
            cout<<endl;
        }
        
    }
}
int main()
{
    struct one_byte object;
    get_string(object);
    for(int j =0;j<num;j++)
    {
        user_code = code[j];
        mov(object);
        mvi(object);
        lxi(object);
        add(object);
        adi(object);
        flag(object);

    }
    
    
}