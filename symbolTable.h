#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

  /*
   *    Description: Adds a symbot to the symbol table
   *    Input: The new symbol
   *          
   *             
   */
void add_symbol_to_list(symbol_node_ptr p_new_symbol);

  /*
   *     Description: create new symbol node
   *     Input: 1.      Name of the new symbol
   *            2.      Address of the new symbol
   *            3.      If it is extern
   *            4.      If it is instruction
   *     Output:    The new symbol node
   */

symbol_node_ptr create_symbol(char* name, unsigned int address, bool is_extern, bool is_instruction);


/*
 *        Description: Search symbol name in symbol list
 *        Input:       Symbol name
 *        Output:      Current symbol node
 *     
 */
symbol_node_ptr search_symbol(char* symbol_name);
 /* Description: Free symbol list from memory */
 void free_symbol_list();
#endif /* SYMBOLTABLE_H_ */
