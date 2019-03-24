/*
 * srv6_end.c
 *
 * Copyright (c) 2019 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <vpp/app/version.h>
#include <srv6-end/srv6_end.h>

static void
clb_dpo_lock_srv6_end_m_gtp4_e (dpo_id_t * dpo)
{
}

static void
clb_dpo_unlock_srv6_end_m_gtp4_e (dpo_id_t * dpo)
{
}

static u8 *
clb_dpo_format_srv6_end_m_gtp4_e (u8 * s, va_list * args)
{
  // TODO:
  index_t index = va_arg (*args, index_t);
  CLIB_UNUSED (u32 indent) = va_arg (*args, u32);

  return (format (s, "SR: dynamic_proxy_index:[%u]", index));
}

const static dpo_vft_t dpo_vft = {
  .dv_lock = clb_dpo_lock_srv6_end_m_gtp4_e,
  .dv_unlock = clb_dpo_unlock_srv6_end_m_gtp4_e,
  .dv_format = clb_dpo_format_srv6_end_m_gtp4_e,
};

const static char *const srv6_end_nodes[] = {
  "srv6-end-m-gtp4-e",
  NULL,
};

const static char *const *const dpo_nodes[DPO_PROTO_NUM] = {
  [DPO_PROTO_IP6] = srv6_end_nodes,
};

static u8 fn_name[] = "SRv6-End.M.GTP4.E-plugin";
static u8 keyword_str[] = "End.M.GTP4.E";
static u8 def_str[] = "Endpoint function with encapsulation for IPv4/GTP tunnel";
static u8 param_str[] = "";

static u8 *
clb_format_srv6_end_m_gtp4_e (u8 * s, va_list * args)
{
  // TODO: we may not need this, string s contains the command line
  // output to be printed 
  s = format (s, "SRv6 End format function unsupported.");
  return s;
}

static uword *
clb_unformat_srv6_end_m_gtp4_e (unformat_input_t, va_list * args)
{
  // TODO: we need this! process the parameters of command line
}

static int
clb_creation_srv6_end_m_gtp4_e (ip6_sr_localsid_t * localsid)
{
  // TODO: figure out what to do
}

static int
clb_removal_srv6_end_m_gtp4_e (ip6_sr_localsid_t * localsid)
{
  // TODO: figure out what to do
}

static clib_error_t *
srv6_end_init (vlib_main_t * vm)
{
  srv6_end_main_t *sm = &srv6_end_main;
  vlib_node_t *node;
  u32 rc;

  dpo_type_t dpo_type;

  sm->vlib_main = vm;
  sm->vnet_main = vnet_get_main ();
                                
  node = vlib_get_node_by_name (vm, (u8 *) "srv6-end-m-gtp4-e");
  sm->end_m_gtp4_e_node_index = node->index;

  node = vlib_get_node_by_name (vm, (u8 *) "error-drop");
  sm->error_node_index = node->index;

  dpo_type = dpo_register_new_type (&dpo_vft, dpo_nodes);

  rc = sr_localsid_register_function (vm, fn_name, keyword_str,
                                      def_str, param_str, &dpo_type,
                                      clb_format_srv6_end_m_gtp4_e,
                                      clb_unformat_srv6_end_m_gtp4_e,
                                      clb_creation_srv6_end_m_gtp4_e,
                                      clb_removal_srv6_end_m_gtp4_e);
  if (rc < 0)
    {
      clib_error_return (0, "SRv6 Endpoint LocalSID function"
                            "couldn't be registered");
    }
   
  return 0;
}

/* *INDENT-OFF* */
// TODO: check if name matters !
VNET_FEATURE_INIT (srv6_end_m_gtp4_e, static) =
{
  .arc_name = "ip6-unicast",
  .node_name = "srv6-end-m-gtp4-e",
  .runs_before = 0,
};

VLIB_INIT_FUNCTION (srv6_end_init);

VLIB_PLUGIN_REGISTER () = {
  .version = VPP_BUILD_VER,
  .description = "SRv6 Endpoint",
};
/* *INDENT-ON* */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
