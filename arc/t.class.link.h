.//============================================================================
.// Notice:
.// (C) Copyright 1998-2013 Mentor Graphics Corporation
.//     All rights reserved.
.//
.// This document contains confidential and proprietary information and
.// property of Mentor Graphics Corp.  No part of this document may be
.// reproduced without the express written permission of Mentor Graphics Corp.
.//============================================================================
.//
.if ( te_relinfo.multiplicity == 0 )
  .// navigation across link to ONE
  .if ( navigated or te_c.OptDisabled )
    .if ( not te_relinfo.is_supertype )
#define ${navigate_method.result}( ${te_class.Key_Lett} ) ( (${te_class.Key_Lett})->${member_data_name.result} )
    .else
      .// Note:  Macros fully parenthesized to placate feeble compilers.
#define ${navigate_method.result}( ${te_class.Key_Lett} ) \\
   ( (((${te_class.Key_Lett})->${member_data_name.obj_id}) == ${related_te_class.system_class_number}) ? \\
     ((${related_te_class.GeneratedName} *)((${te_class.Key_Lett})->${member_data_name.result})) : (0) )
    .end if
  .end if
.else
  .// navigation across link to MANY
  .if ( navigated or te_c.OptDisabled )
#define ${navigate_method.result}( ${te_class.Key_Lett} ) ( &((${te_class.Key_Lett})->${member_data_name.result}) )
  .end if
.end if
.if ( not navigated )
/* Note:  ${te_class.Key_Lett}->${related_te_class.Key_Lett}[R${rel.Numb}] not navigated */
.end if
.//
