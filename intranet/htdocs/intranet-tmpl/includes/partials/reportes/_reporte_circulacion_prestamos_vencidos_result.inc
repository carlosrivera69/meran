
<fieldset>
    <legend class="titulo_legend">[% "Pr&eacute;stamos vencidos" | i18n %] </legend>

 [% IF cantidad  %]

             [% PERL %]
                 print C4::AR::Filtros::sortableTableHeader(   
                                                         id                 => "prestamosVencidos",
                                                         class              => "table table-bordered",
                                                         columns            => ["<i id='prestamos_vencidos' class='icon-ok-sign click' title='Seleccionar todos'></i>",'[% "Apellido y nombre"|i18n %]','[% "N&uacute;mero de Socio"|i18n %]','[% "Ejemplar"|i18n %]', '[% "Tipo de pr&eacute;stamo"|i18n %]','[% "Fecha de pr&eacute;stamo"|i18n %]', '[% "Fecha de vencimiento"|i18n %]'
                                                                            ],
                                                         sortable_fields    => {  
                                                                               'Apellido y nombre'      => 'apellido', 
                                                                               'Fecha de pr&eacute;stamo'  => 'fecha_prestamo',
                                                                               'Fecha de vencimiento'   => 'fecha_vto'
                                                                             },
                                                        order               => "[% orden %]",
                                                        order_direction     => "[% sentido_orden %]",
                                                        order_name_function => "reporte_prestamos_vencidos"
                                                        
                                                         
                             ) ;
             [% END %]        

          [% FOREACH prestamo IN prestamos %]
            <tr>
                <td>
                <input type="checkbox" id="[% prestamo.getId_prestamo %]" name="prestamo" >
            </td>
                <td>
                  [% TRY %]
                      [% prestamo.socio.persona.getApeYNom %]
                  [% CATCH %]
                      [% 'Usuario inexistente' | i18n %]
                  [% END %]
            </td>
                <td>
                      [% TRY %]
                        [% PERL %]
                            print C4::AR::Filtros::link_to(   text   => "[% prestamo.socio.getNro_socio %]",
                                                              url    => "[% url_prefix %]/usuarios/reales/datosUsuario.pl",
                                                              params => ["nro_socio=[% prestamo.socio.getNro_socio %]"],
                                                              title  => "[% 'Mostrar Detalle del Usuario' | i18n %]",
                                                              blank  => 1,
                                                        );
                        [% END %]
                      [% CATCH %]
                          [% 'Usuario inexistente' | i18n %] ([% prestamo.nro_socio %])
                      [% END %]
            </td>
            <td>
                    [% PERL %]
                            print C4::AR::Filtros::link_to( text    => "[% prestamo.nivel3.codigo_barra %]",
                                                            url     => "[% url_prefix %]/catalogacion/estructura/detalleEjemplar.pl", 
                                                            params  => ["id3=[% prestamo.nivel3.getId3 %]"],
                                                            title   => "[% prestamo.nivel3.codigo_barra %]"
                                                        );
                    [% END %]
            </td>
                <td>
                    [% prestamo.tipo.getDescripcion %]
            </td>
            <td>
                    [% prestamo.getFecha_prestamo_formateada %]
            </td>
            <td>
                    <span class="label label-important">[% prestamo.getFecha_vencimiento_reporte_formateada %]</span>
            </td>
            </tr>
          [% END %]

  </table>
[% ELSE %]
        <div class="alert alert-info">[% "No hay pr&eacute;stamos vencidos" | i18n %]</div> 
[% END %]


</fieldset>