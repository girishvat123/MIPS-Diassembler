#include<iostream>
#include<stdio.h>
#include<fstream>
#include<math.h>
#include<cstring>
#include<cstdlib>
#include<iomanip>
using namespace std;

int main()
{
	string filelocn;
	char state='0';
cout<<"Enter the path of the input text file\n";
cin>>filelocn;
int memaddr=492;
//provides the input operations for the file
//.c_str is used to get as a word.it will move to the next line after each word
ifstream binaryfile(filelocn.c_str(),ios::in);
ofstream ouputfile("output.txt",ios::out);
if (ouputfile.is_open())
{
while (!binaryfile.eof())
{
memaddr=memaddr+4;
//get the input binary file
string in;
binaryfile>>in;
string opncode,rd,rs,rt,shift_amnt,func;
int bin_rd, bin_rs, bin_rt, bin_shift_amnt, bin_imm_off,bin_imm_offset, bin_imm_off_unsigned, binary_to_integer, binary_jumptarget;
//now split the binary input into opncode,rs,rt,shft_amont,func using substr function
opncode=in.substr(0,6);
rs=in.substr(6,5);
rt=in.substr(11,5);
rd=in.substr(16,5);
shift_amnt=in.substr(21,5);
func=in.substr(26,6);


unsigned int value_integer=0;
int bit_pos;
//Reset to erase previous bit position values.
for(bit_pos = 0; bit_pos < 32; bit_pos++)
if(in[bit_pos] == '1')
value_integer	=	value_integer | (1 << (31-bit_pos));
//convert the integer value to decimal value use bitwise operator
binary_to_integer	=	value_integer;
binary_jumptarget	=	(value_integer & (0x3FFFFFF))<<2;
bin_imm_off 	=	(value_integer & (0x0000FFFF));
//binary immediate offset for  all branch instruction
bin_imm_offset=	(value_integer & (0x0000FFFF))<<2;
bin_imm_off_unsigned	= ( ~(value_integer) & (0x0000FFFF) ) + 1;
bin_rd = (value_integer & (0xF800) ) >> 11;
bin_rs = (value_integer & (0x3E00000) ) >> 21;
bin_rt = (value_integer & (0x1F0000)) >> 16;
bin_shift_amnt   = (value_integer & (0x7C0) ) >> 6;

if(state=='0')
{
	//R Type Instruction
	if((opncode=="000000")&(shift_amnt=="00000"))
	{
	if(func=="100000")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADD"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<" ,"<<"R"<<bin_rt<<endl;
	else if(func=="100001")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADDU"<<"  "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<" "<<"R"<<bin_rt<<endl;
	else if (func=="100100")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"AND"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<" "<<"R"<<bin_rt<<endl;
	else if(func=="100010")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SUB"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<" "<<"R"<<bin_rt<<endl;
	else if (func=="100011")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SUBU"<<"  "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<" "<<"R"<<bin_rt<<endl;
	else if (func=="101010")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SLT"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<endl;
	else if(func=="100111")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"NOR"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<endl;
	else if(func=="100101")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"OR"<<"    "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<endl;
	else if(func=="100110")
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"XOR"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<endl;
	else if((opncode=="000000")&&(rs=="00000")&&(rt=="00000")&&(rd=="00000")&&(shift_amnt=="00000")&&(func=="001101"))
				{
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<""<<"BREAK"<<endl;
				    state = '2';	//change to any other value except '0'.
				}
	else if((opncode=="000000")&&(rs=="00000")&&(rt=="00000")&&(rd=="00000")&&(shift_amnt=="00000")&&(func=="000000"))
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"NOP"<<endl;
	else if((opncode=="000000")&&(rt=="00000")&&(rd=="00000")&&(shift_amnt=="00000")&&(func=="001000"))
	ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"JR"<<"    "<<"R"<<bin_rs<<endl;

	}
	else if((opncode=="000000")&&(rs=="00000"))
	{
		if(func=="000000")
		ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SLL"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rt<<", "<<"R"<<bin_shift_amnt<<endl;
        else if(func=="000010")
		ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SRL"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rt<<", "<<"R"<<bin_shift_amnt<<endl;
	    else if(func=="000011")
		ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SRA"<<"   "<<"R"<<bin_rd<<", "<<"R"<<bin_rt<<", "<<"R"<<bin_shift_amnt<<endl;
	}

	//I Type Instruction
	else if((opncode=="001000")&&(rd=="11111"))
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADDI"<<"  "<<"R"<<bin_rt<<", "<<"R"<<bin_rs<<", "<<"#"<<"-"<<bin_imm_off_unsigned<<endl;

		else if(opncode=="001000")
		ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADDI"<<"  "<<"R"<<bin_rt<<", "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_off<<endl;

				else if((opncode=="001001")&&(rd=="11111"))
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADDIU"<<" "<<"R"<<bin_rt<<", "<<"R"<<bin_rs<<", "<<"#"<<"-"<<bin_imm_off_unsigned<<endl;
				else if(opncode=="001001")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"ADDIU"<<" "<<"R"<<bin_rt<<", "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_off<<endl;
                else if(opncode=="000100")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BEQ"<<"   "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<", "<<"#"<<bin_imm_offset<<endl;
                else if(opncode=="001010")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SLTI"<<"  "<<"R"<<bin_rt<<", "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_off<<endl;	
                else if(opncode=="000101")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BNE"<<"   "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<", "<<"#"<<bin_imm_offset<<endl;
                else if(opncode=="000100")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BEQ"<<"   "<<"R"<<bin_rs<<", "<<"R"<<bin_rt<<", "<<"#"<<bin_imm_offset<<endl;
                 else if((opncode=="000111")&& (rt=="00000"))
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BGTZ"<<"  "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_offset<<endl;
				else if((opncode=="000001")&& (rt=="00000"))
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BLTZ"<<"  "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_offset<<endl;
				else if((opncode=="000110")&& (rt=="00000"))
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"BLEZ"<<"  "<<"R"<<bin_rs<<", "<<"#"<<bin_imm_offset<<endl;
				else if(opncode=="100011")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"LW"<<"    "<<"R"<<bin_rt<<", "<<bin_imm_off<<"(R"<<bin_rs<<")"<<endl;
				else if(opncode=="101011")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"SW"<<"    "<<"R"<<bin_rt<<", "<<bin_imm_off<<"(R"<<bin_rs<<")"<<endl;
               // J Type Instruction
				else if(opncode=="000010")
				    ouputfile<<opncode<<"  "<<rs<<"  "<<rt<<"  "<<rd<<"  "<<shift_amnt<<"  "<<func<<"  "<<memaddr<<"  "<<"J"<<"     "<<"#"<<binary_jumptarget<<endl;
				// Break Instruction


}
//To enter binary value of the 32bit valued string
   			else
			{

					ouputfile<<in<<setw(15)<<memaddr<<"  "<<binary_to_integer<<endl;

			}


}


}
binaryfile.close();
	ouputfile.close();
	system("pause");
	return 0;
}
