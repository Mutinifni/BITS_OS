/* This file will include the functions and the declarations provided while setting up the global descriptor table. */  
/* We will inteface this file with the assembly. */ 
/*
 There are two steps in transforming a logical address into physical address :- 
1) Segment translation :- the logical address will be given to us in the form (CS : IP), we will convert it into a linear address. 
2) Page translation :-  In this we convert the previously computer linear address into a physical address. Since, we are using a simple flat memory model, we won't be needing this step as the previously computed step will be a phsyical address as well .   

Now, we will see how to do segment translation using the Intel 80386  processor. To perform segment translation the processor uses the following data structures : - 
1) Descriptors 
2) Descriptor tables. 
3) Selectors. 
4) Segment registers
 
The individual entries present in the global descriptor table is individually called as descriptor. Each descriptor is 8 bytes (64 bits) long and a descriptor table can store upto
2^13 descriptors in it.  The descriptor at index 0 is never used by the processor and it is what we never use.
    
Descriptor : -  As told previously, each descriptor is 64 bits long. It's contents are BASE(32 bits), LIMIT(20 bits), granularity(1 bit), type(unknown bits),descriptor privelage level(unknown bits), segment present bit (1 bit) , accessed bit(1 bit).      

Descriptor Table :- This is the table which will contain the descriptors described above.  There are two types of descriptor tables in operating system, global descriptor table or the local descriptor table. 

Selectors :- To identify a particular entry in the GDT or the LDT (ie access a particular descriptor), we have selectors. When the compiler compiles our program or the linker links our program,these details are implicitly stored in the variables we define when we write a program. These selectors are 16 bit wide and contain the following information.  
a) Segment Value (b/w 0 and 8192) :- 12 bits, 
b) Table indicator(0 or 1) :- 1 bit :- 0 indicates local descriptor table and 1 indicates global descriptor table. 
c) Request level privelage :- 4 bits :- It indicates the required privelage level when accessing the memory address.   

Segment Registers :- These are the normal registers present in the processor. They are :- CS, DS, ES, FS, GS.  These registers have a 16 bit visible value which is visble to the programmer while the invisible part is not visible to the programmer. 

Here. ends the description of how to setup the global desriptor table. 
*/ 
/* The code we are writing is guaranteed to work on a 32 bit computer. No guarantee for 64 bit computer !*/  
/* Although, the description of the descriptor tends to be correct, in many places this is presented in a different way. */ 
/* Include all these header files from the include file we have made in our operating system. */ 
extern void gdt_flush()  ; 
#define uint32_t unsigned int 
#define uint16_t unsigned short
#define uint8_t unsigned char 
uint32_t gdt_address ; 
struct descriptor 
{
	uint16_t limit_low ; 
	uint16_t base_low ; 
	uint8_t base_middle ; 
	uint8_t base_high ; 
	uint8_t access ; 
	uint8_t granularity ; 
} __attribute__((packed)) ;   // no compiler optimiztion needed. 

typedef struct descriptor descriptor ;  

// Now we will construct a pointer which will point to the global descriptor table actually present in the memory.  

struct gdt_ptr
{
	uint16_t limit ; // limit is the size of the gdt -1 
	uint32_t base ; // base address of the gdt. 
} __attribute__((packed));  

typedef struct gdt_ptr gdt_ptr ;   
// now we will create a array of the descriptor structure and that will be our gdt.  
// We will also make a assembly file which will load the gdt using the assembly instructions.

/* Setup a descriptor in the Global Descriptor Table */
// Define some global variables here. 
descriptor gdt[3] = { } ; 
gdt_ptr gp  ; 
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install(uint32_t size)
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct descriptor) * size) - 1;
    gp.base = (uint32_t)&gdt;
    gdt_address = gp.base ; 

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
    *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
    *  uses 32-bit opcodes, and is a Code Segment descriptor.
    *  Please check the table above in the tutorial in order
    *  to see exactly what each value means */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);            

    /* The third entry is our Data Segment. It's EXACTLY the
    *  same as our code segment, but the descriptor type in
    *  this entry's access byte says it's a Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Flush out the old GDT and install the new changes! */
    gdt_flush();
}
		
